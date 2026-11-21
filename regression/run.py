#!/usr/bin/env python3
"""Runs one regression test. The test is a C or IR file whose comment header
describes it:

    // RUN: <flags for vereda.py>            optional, default none
    // EXPECT: <regex>                       must match the output (re.MULTILINE)
    // EXPECT-NOT: <regex>                   must not match
    // MODE: CORE|THOROUGH|KNOWNBUG|FUTURE   optional, default CORE
    // FILES: a.c b.c                        extra sources, relative to the test

IR files use ';' instead of '//'. KNOWNBUG and FUTURE tests are expected to
fail; the run then passes exactly when some expectation does not hold.
The tool runs in a fresh temporary directory, so output files never land in
the source tree."""
import argparse
import os
import re
import subprocess
import sys
import tempfile

HEADER = re.compile(r"^\s*(?://|;)\s*(RUN|EXPECT|EXPECT-NOT|MODE|FILES):\s*(.*?)\s*$")
FAIL_MODES = ("KNOWNBUG", "FUTURE")


def parse(path):
    desc = {"RUN": "", "EXPECT": [], "EXPECT-NOT": [], "MODE": "CORE", "FILES": ""}
    with open(path, encoding="utf-8", errors="replace") as f:
        for line in f:
            m = HEADER.match(line)
            if not m:
                continue
            key, value = m.groups()
            if key in ("EXPECT", "EXPECT-NOT"):
                desc[key].append(value)
            else:
                desc[key] = value
    return desc


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--vereda", required=True, help="path to vereda.py")
    parser.add_argument("--bin", required=True, help="path to the vereda binary")
    parser.add_argument("--clang", required=True, help="path to clang")
    parser.add_argument("test")
    args = parser.parse_args()

    test = os.path.abspath(args.test)
    desc = parse(test)
    files = [test] + [os.path.join(os.path.dirname(test), f) for f in desc["FILES"].split()]
    cmd = [sys.executable, args.vereda, "--bin", args.bin, "--clang", args.clang]
    cmd += desc["RUN"].split() + files
    with tempfile.TemporaryDirectory(prefix="vereda-regress-") as tmp:
        proc = subprocess.run(cmd, cwd=tmp, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                              text=True, check=False)
    out = proc.stdout

    unmet = [f"EXPECT: {r}" for r in desc["EXPECT"] if not re.search(r, out, re.MULTILINE)]
    unmet += [f"EXPECT-NOT: {r}" for r in desc["EXPECT-NOT"] if re.search(r, out, re.MULTILINE)]
    expected_to_fail = desc["MODE"] in FAIL_MODES
    ok = (not unmet) != expected_to_fail
    if not ok:
        print("+", " ".join(cmd))
        print(out)
        if expected_to_fail:
            print(f"{desc['MODE']} test passed unexpectedly; promote it to CORE")
        for u in unmet:
            print("unmet", u)
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
