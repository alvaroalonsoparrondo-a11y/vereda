# Vereda

A bounded model checker and k-induction prover for C on LLVM IR. Vereda is
Portuguese for a narrow trail: the walker follows every one through the
program. See `docs/plan.md` for the goals and `docs/architecture.md` for the
layout.

## Build

```sh
cmake -S . -B build -G Ninja -DDOWNLOAD_DEPENDENCIES=ON
ninja -C build
ctest --test-dir build
```

`DOWNLOAD_DEPENDENCIES=ON` fetches the pinned LLVM 21 and camada releases into
`build/deps` and builds with that LLVM's clang and lld. With it off, set
`LLVM_DIR` (LLVM 21 to 23) and `camada_DIR` to installed copies.

## Run

```sh
./vereda.py --clang build/deps/llvm/LLVM-21.1.8-Linux-X64/bin/clang file.c
```

`vereda.py -h` lists the front-end flags followed by the binary's.

## Tests

A test is a C or IR file under `regression/<suite>/` whose comment header
says how to run it and what to expect:

```c
// RUN: --unwind 5
// EXPECT: ^VERIFICATION FAILED$
// EXPECT-NOT: VERIFICATION SUCCESSFUL
// MODE: FUTURE          (optional: CORE, THOROUGH, KNOWNBUG, FUTURE)
// FILES: helper.c       (optional: extra sources next to the test)
```

`ctest -L <suite>` runs one suite. KNOWNBUG and FUTURE tests must fail; a
run that passes asks to be promoted.
