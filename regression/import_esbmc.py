#!/usr/bin/env python3
"""Copies ESBMC's C regression tests into Vereda's format.

    regression/import_esbmc.py ~/tools/esbmc/regression [suite ...]

Each ESBMC test <suite>/<test>/ with a C input becomes
regression/<name>/<test>/main.c plus the test's other files, where <name>
is the suite, prefixed with "esbmc-" unless it already starts with "esbmc".
The test.desc goes into a comment header at the end of main.c, so that line
numbers in the expected output still hold. A rerun replaces earlier copies.

ESBMC flags with a Vereda equivalent are translated. Flags that only turn
off a check Vereda does not have are dropped. A test that needs any other
flag keeps its ESBMC flags and becomes FUTURE, with the missing flags named
in a "// Needs:" line; Vereda then rejects the flags, so the test passes
until Vereda learns them and the script runs again. ESBMC's REQUIRES,
CHECK_JSON, CHECK_FILE and SEED_FILE lines make a test FUTURE the same way,
as run.py has none of them.

Tests that read files outside their own directory are skipped, and so is
ESBMC's "disabled" suite unless named."""
import argparse
import os
import re
import shlex
import shutil
import sys

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


def import_test(src, dest, origin):
    """Copies one test from src to dest. Returns "copied", or why not."""
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

    shutil.rmtree(dest, ignore_errors=True)
    shutil.copytree(src, dest, ignore=shutil.ignore_patterns("test.desc"))
    entry = os.path.join(dest, "main.c")
    if source != "main.c":
        os.replace(os.path.join(dest, source), entry)
        # The output names the source file, so the expectations follow it.
        old = re.compile("".join(r"\\?\." if c == "." else re.escape(c) for c in source))
        regexes = [old.sub("main.c", r) for r in regexes]

    with open(entry, "rb") as f:
        newline = b"" if f.read().endswith(b"\n") else b"\n"
    with open(entry, "ab") as f:
        f.write(newline + ("\n".join(header(origin, mode, args, regexes, src)) + "\n").encode())
    return "copied"


def main():
    """Imports the suites named on the command line, or all of them."""
    here = os.path.dirname(os.path.abspath(__file__))
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("esbmc", help="ESBMC's regression directory")
    parser.add_argument("suites", nargs="*", help="suites to import (default: all but disabled)")
    parser.add_argument("--out", default=here, help="where suites go (default: regression/)")
    args = parser.parse_args()

    suites = args.suites or sorted(d for d in os.listdir(args.esbmc) if d != "disabled"
                                   and os.path.isdir(os.path.join(args.esbmc, d)))
    for suite in suites:
        counts = {}
        for root, _, names in os.walk(os.path.join(args.esbmc, suite)):
            if "test.desc" not in names:
                continue
            rel = os.path.relpath(root, os.path.join(args.esbmc, suite))
            dest = os.path.join(args.out, suite_name(suite), rel.replace(os.sep, "__"))
            result = import_test(root, dest, os.path.join(suite, rel))
            counts[result] = counts.get(result, 0) + 1
        copied = counts.pop("copied", 0)
        counts.pop("not C", None)
        if copied or counts:
            skipped = "".join(f", {n} skipped: {why}" for why, n in sorted(counts.items()))
            print(f"{suite}: {copied} copied to {suite_name(suite)}{skipped}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
