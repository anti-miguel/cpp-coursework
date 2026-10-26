# Recursive pairing of arrays

Recursively pairs parallel arrays of ages and neutral person labels, then recursively prints the resulting records.

Demonstrates: Structs, parallel arrays, recursion, and base cases.

## Build and run

From the repository root:

```sh
cmake -S . -B build
cmake --build build --config Release --target recursive_pairs_cosa
./build/bin/recursive_pairs_cosa
```

For a Visual Studio build, use `build/bin/Release/`; Windows executables end in `.exe`. See the [root build instructions](../../README.md#build-and-run).

No input is required. The demonstration prints five records. Person labels are placeholders replacing the original sample names.

## Targets

| Target | Source | Platform |
| --- | --- | --- |
| `recursive_pairs_cosa` | `cosa.cpp` | Portable |
