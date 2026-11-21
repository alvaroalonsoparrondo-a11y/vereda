#!/usr/bin/env python3
"""Front-end vereda.py: compiles C to LLVM bitcode with clang and runs the
verifier binary on it. Only front-end flags are defined here; every other
argument is forwarded to the binary unchanged, so each flag lives in one
place. Inputs are recognised by extension (.c .i .ll .bc)."""
import argparse
import os
import shutil
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
SOURCE_EXTS = (".c", ".i")
IR_EXTS = (".ll", ".bc")

CLANG_FLAGS = [
    "-g", "-O0", "-emit-llvm", "-c",
    # C11 lets the compiler assume loops without side effects terminate;
    # clang would mark them mustprogress and the binary rejects that.
    "-fno-finite-loops",
    # ponytail: no -fsanitize checks until the overflow and bounds properties
    # (plan section 7.2) are encoded.
]


def find_binary():
    for candidate in (os.path.join(HERE, "vereda"),
                      os.path.join(HERE, "build", "vereda"),
                      shutil.which("vereda")):
        if candidate and os.access(candidate, os.X_OK):
            return candidate
    sys.exit("vereda.py: verifier binary not found; pass --bin")


def main():
    parser = argparse.ArgumentParser(add_help=False, description=__doc__)
    parser.add_argument("-h", "--help", action="store_true")
    parser.add_argument("--bin", help="verifier binary (default: next to this script or build/)")
    parser.add_argument("--clang", default=os.environ.get("CLANG", "clang"),
                        help="clang of the same LLVM version as the binary (default: $CLANG or clang)")
    parser.add_argument("-m32", action="store_true", help="32-bit target, forwarded to clang")
    parser.add_argument("-m64", action="store_true", help="64-bit target, forwarded to clang")
    parser.add_argument("-I", action="append", default=[], help="include directory for clang")
    parser.add_argument("-D", action="append", default=[], help="macro definition for clang")
    parser.add_argument("--keep-ir", action="store_true",
                        help="write the IR handed to the binary next to the input as <input>.ll")
    parser.add_argument("-v", "--verbose", action="store_true", help="echo every command run")
    args, rest = parser.parse_known_args()
    arch = ["-m32"] * args.m32 + ["-m64"] * args.m64

    binary = args.bin or find_binary()
    if args.help:
        parser.print_help()
        print("\nBinary options:\n")
        sys.stdout.flush()
        return subprocess.call([binary, "--help"])

    inputs = [a for a in rest if a.endswith(SOURCE_EXTS + IR_EXTS)]
    forwarded = [a for a in rest if a not in inputs]
    if len(inputs) != 1:
        # ponytail: one input; llvm-link the rest when a task needs it.
        sys.exit("vereda.py: expected exactly one input file, got %r" % inputs)
    source = inputs[0]

    def run(cmd):
        if args.verbose:
            print("+", " ".join(cmd), file=sys.stderr)
        sys.stdout.flush()
        return subprocess.call(cmd)

    run([binary, "--version"])
    with tempfile.TemporaryDirectory() as tmp:
        ir = source
        if source.endswith(SOURCE_EXTS):
            print("[PROGRESS] Compiling", source)
            ir = os.path.join(tmp, os.path.basename(source) + (".ll" if args.keep_ir else ".bc"))
            cmd = ([args.clang] + CLANG_FLAGS + arch + ["-I" + d for d in args.I]
                   + ["-D" + d for d in args.D] + (["-S"] if args.keep_ir else [])
                   + [source, "-o", ir])
            if run(cmd) != 0:
                return 1
            if args.keep_ir:
                shutil.copy(ir, source + ".ll")
        return run([binary] + forwarded + [ir])


if __name__ == "__main__":
    sys.exit(main())
