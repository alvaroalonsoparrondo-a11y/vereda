#!/usr/bin/env python3
"""Copies ESBMC's C regression tests into Vereda's format.

    regression/import_esbmc.py ~/tools/esbmc/regression [suite ...]

Each ESBMC test <suite>/<test>/ with a C input becomes regression/<name>/
<test>.c when the source is its only file, and <test>/main.c next to the
other files otherwise, where <name> is the suite, prefixed with "esbmc-"
unless it already starts with "esbmc". The test.desc goes into a comment
header at the end of the C file, so that line numbers in the expected
output still hold. A rerun replaces earlier copies.

ESBMC flags with a Vereda equivalent are translated. Flags that only turn
off a check Vereda does not have are dropped. A test that needs any other
flag keeps its ESBMC flags and becomes FUTURE, with the missing flags named
in a "// Needs:" line; Vereda then rejects the flags, so the test passes
until Vereda learns them and the script runs again. ESBMC's REQUIRES,
CHECK_JSON, CHECK_FILE and SEED_FILE lines make a test FUTURE the same way,
as run.py has none of them.

Tests that read files outside their own directory are skipped, and so is
ESBMC's "disabled" suite unless named.

With --mark, each copied test then runs through run.py, and one that does
not behave as its mode says gets the other mode: a failing CORE or THOROUGH
test becomes FUTURE, and a FUTURE or KNOWNBUG test Vereda passes becomes
CORE. A "// Vereda:" line says why. The suite then passes as Vereda is now,
and a later Vereda that fixes a FUTURE test fails it until it is promoted."""
import argparse
import concurrent.futures
import os
import re
import shlex
import shutil
import subprocess
import sys

sys.dont_write_bytecode = True  # no __pycache__ next to the tests
import run  # pylint: disable=wrong-import-position

# ESBMC flag -> Vereda flags; a value, if the flag takes one, follows.
SAME = {"--no-unwinding-assertions", "--incremental-bmc", "--multi-property",
        "--force-malloc-success"}
SAME_WITH_VALUE = {"--unwind", "--max-k-step"}
RENAMED = {
    "--32": ["-m32"], "--64": ["-m64"],
    "--smt-formula-only": ["--dump-smt-only"], "--smt-formula-too": ["--dump-smt-too"],
    "--bitwuzla": ["--solver", "bitwuzla"], "--z3": ["--solver", "z3"],
    "--cvc": ["--solver", "cvc5"], "--cvc5": ["--solver", "cvc5"],
}
RENAMED_WITH_VALUE = {"--function": "--entry"}
# Checks and tuning Vereda does not have, so turning them off changes nothing.
DROPPED = {"--no-pointer-check", "--no-bounds-check", "--no-div-by-zero-check",
           "--no-align-check", "--no-vla-size-check", "--no-pointer-relation-check",
           "--no-simplify", "--no-slice", "--floatbv"}


def translate(args, test_dir):
    """Returns (Vereda flags, extra source files, ESBMC flags Vereda lacks)."""
    flags, files, missing = [], [], []
    tokens = iter(shlex.split(args))
    for tok in tokens:
        name, eq, value = tok.partition("=")
        if not tok.startswith("-"):
            if tok.endswith(".c") and os.path.exists(os.path.join(test_dir, tok)):
                files.append(tok)
            else:
                missing.append(tok)
        elif name in SAME_WITH_VALUE or name in RENAMED_WITH_VALUE:
            value = value if eq else next(tokens, "")
            flags += [RENAMED_WITH_VALUE.get(name, name), value]
        elif tok in SAME:
            flags.append(tok)
        elif tok in RENAMED:
            flags += RENAMED[tok]
        elif tok in DROPPED or tok.startswith("-Wno-"):  # clang already relaxes these
            continue
        elif tok.startswith("-D"):
            flags.append(tok if len(tok) > 2 else tok + next(tokens, ""))
        else:
            missing.append(tok)
    return flags, files, missing


def suite_name(suite):
    """Vereda's directory for an ESBMC suite."""
    return suite if suite.startswith("esbmc") else "esbmc-" + suite


# test.desc lines that are not output regexes.
DIRECTIVES = ("REQUIRES", "CHECK_JSON", "CHECK_FILE", "SEED_FILE")


def header(origin, mode, args, expected, test_dir):
    """The comment header Vereda's run.py reads, for one test.desc."""
    flags, files, missing = translate(args, test_dir)
    regexes = [r for r in expected if r.split()[0] not in DIRECTIVES]
    missing += [r for r in expected if r.split()[0] in DIRECTIVES]
    lines = [f"// Imported from ESBMC regression/{origin}"]
    if missing:
        lines += ["// Needs: " + " ".join(missing), "// RUN: " + args]
        mode = "KNOWNBUG" if mode == "KNOWNBUG" else "FUTURE"
    elif flags:
        lines.append("// RUN: " + " ".join(flags))
    if files:
        lines.append("// FILES: " + " ".join(files))
    if mode != "CORE":
        lines.append("// MODE: " + mode)
    return lines + ["// EXPECT: " + r for r in regexes]


def outside(test_dir, path):
    """Whether path, relative to test_dir, leaves it."""
    real = os.path.realpath(os.path.join(test_dir, path))
    return os.path.commonpath([real, os.path.realpath(test_dir)]) != os.path.realpath(test_dir)


def copy_files(src, dest, source, tracked):
    """Copies the test's files from src, renaming source to dest.c when it
    is the only one and to dest/main.c otherwise. Returns that path, or
    None when another file is already main.c."""
    def ignored(directory, names):
        # A test's directory can hold other tests; each is copied on its own.
        def untracked(p):
            return tracked is not None and os.path.isfile(p) and os.path.realpath(p) not in tracked
        paths = {n: os.path.join(directory, n) for n in names}
        return {n for n, p in paths.items() if n == "test.desc" or untracked(p)
                or os.path.exists(os.path.join(p, "test.desc"))}

    shutil.rmtree(dest, ignore_errors=True)
    if os.path.exists(dest + ".c"):
        os.remove(dest + ".c")
    shutil.copytree(src, dest, ignore=ignored)
    for root, _, _ in os.walk(dest, topdown=False):  # what the filters emptied
        if not os.listdir(root):
            os.rmdir(root)
    if os.listdir(dest) == [source]:
        os.replace(os.path.join(dest, source), dest + ".c")
        os.rmdir(dest)
        return dest + ".c"
    if source != "main.c" and os.path.exists(os.path.join(dest, "main.c")):
        shutil.rmtree(dest)
        return None
    os.replace(os.path.join(dest, source), os.path.join(dest, "main.c"))
    return os.path.join(dest, "main.c")


def import_test(src, dest, origin, tracked):
    """Copies one test from src to dest, or to dest.c when it has one file.
    Returns the C file written, or why there is none. When tracked is a set
    of paths, files outside it are left behind."""
    with open(os.path.join(src, "test.desc"), encoding="utf-8", errors="replace") as f:
        lines = f.read().split("\n")
    if len(lines) < 3 or not lines[1].strip().endswith(".c"):
        return "not C"
    mode, source, args = (line.strip() for line in lines[:3])
    try:
        paths = [source] + [t for t in shlex.split(args) if not t.startswith("-")]
    except ValueError:
        return "unreadable flags"
    if any(outside(src, p) for p in paths):
        return "files outside the test"
    regexes = [r.strip() for r in lines[3:] if r.strip()]

    entry = copy_files(src, dest, source, tracked)
    if not entry:
        return "a main.c besides the source"
    name = os.path.basename(entry)
    if source != name:
        # The output names the source file, so the expectations follow it.
        old = re.compile(r"(?<![\w-])" + "".join(r"\\?\." if c == "." else re.escape(c)
                                                 for c in source))
        regexes = [old.sub(lambda _: re.escape(name), r) for r in regexes]

    with open(entry, "rb") as f:
        newline = b"" if f.read().endswith(b"\n") else b"\n"
    with open(entry, "ab") as f:
        f.write(newline + ("\n".join(header(origin, mode, args, regexes, src)) + "\n").encode())
    return entry


def mark(tests, runner):
    """Runs each test with runner, the run.py command line without the test,
    and flips the mode of those that do not behave as their mode says.
    Returns how many were flipped."""
    def check(test):
        return test, subprocess.run(runner + [test], stdout=subprocess.PIPE,
                                    stderr=subprocess.STDOUT, text=True, check=False)

    flipped = 0
    with concurrent.futures.ThreadPoolExecutor(os.cpu_count()) as pool:
        for test, proc in pool.map(check, tests):
            if proc.returncode in (0, run.SKIPPED):
                continue
            mode = "CORE" if run.parse(test)["MODE"] in run.FAIL_MODES else "FUTURE"
            lines = proc.stdout.splitlines()
            why = ([l for l in lines if l.startswith(("unmet", "TIMEOUT"))] or lines[-1:])[:1]
            with open(test, "a", encoding="utf-8") as f:
                f.write("".join(f"// Vereda: {w[:150]}\n" for w in why) + f"// MODE: {mode}\n")
            flipped += 1
    return flipped


def main():
    """Imports the suites named on the command line, or all of them."""
    here = os.path.dirname(os.path.abspath(__file__))
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("esbmc", help="ESBMC's regression directory")
    parser.add_argument("suites", nargs="*", help="suites to import (default: all but disabled)")
    parser.add_argument("--out", default=here, help="where suites go (default: regression/)")
    parser.add_argument("--mark", action="store_true", help="run each test and flip its mode "
                        "when Vereda disagrees; needs --bin and --clang")
    parser.add_argument("--bin", help="the vereda binary, for --mark")
    parser.add_argument("--clang", help="clang matching the binary, for --mark")
    parser.add_argument("--timeout", default="60", help="seconds per test, for --mark")
    args = parser.parse_args()
    if args.mark and not (args.bin and args.clang):
        parser.error("--mark needs --bin and --clang")

    copied_tests = import_suites(args)
    if args.mark:
        runner = [sys.executable, os.path.join(here, "run.py"),
                  "--vereda", os.path.join(os.path.dirname(here), "vereda.py"),
                  "--bin", os.path.abspath(args.bin), "--clang", os.path.abspath(args.clang),
                  "--timeout", args.timeout]
        print(f"{mark(copied_tests, runner)} of {len(copied_tests)} tests changed mode")
    return 0


def tracked_files(esbmc):
    """The real paths of the files git tracks under esbmc, or None when it is
    not a checkout. A working tree also has what earlier runs wrote."""
    git = subprocess.run(["git", "-C", esbmc, "ls-files", "-z", "--full-name"],
                         stdout=subprocess.PIPE, stderr=subprocess.DEVNULL, check=False)
    if git.returncode != 0:
        return None
    top = subprocess.run(["git", "-C", esbmc, "rev-parse", "--show-toplevel"],
                         stdout=subprocess.PIPE, text=True, check=True).stdout.strip()
    return {os.path.realpath(os.path.join(top, p.decode())) for p in git.stdout.split(b"\0") if p}


def import_suites(args):
    """Copies the suites args names, printing a line per suite. Returns the
    main.c of each copied test."""
    suites = args.suites or sorted(d for d in os.listdir(args.esbmc) if d != "disabled"
                                   and os.path.isdir(os.path.join(args.esbmc, d)))
    tracked = tracked_files(args.esbmc)
    copied_tests = []
    for suite in suites:
        counts = {}
        for root, _, names in os.walk(os.path.join(args.esbmc, suite)):
            if "test.desc" not in names:
                continue
            rel = os.path.relpath(root, os.path.join(args.esbmc, suite))
            name = "root" if rel == "." else rel.replace(os.sep, "__")
            dest = os.path.join(args.out, suite_name(suite), name)
            result = import_test(root, dest, os.path.join(suite, rel), tracked)
            if result.endswith(".c"):
                copied_tests.append(result)
                result = "copied"
            counts[result] = counts.get(result, 0) + 1
        copied = counts.pop("copied", 0)
        counts.pop("not C", None)
        if copied or counts:
            skipped = "".join(f", {n} skipped: {why}" for why, n in sorted(counts.items()))
            print(f"{suite}: {copied} copied to {suite_name(suite)}{skipped}")
    return copied_tests


if __name__ == "__main__":
    sys.exit(main())
