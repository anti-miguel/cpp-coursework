# Unary tape multiplication

Represents two nonnegative integers as unary runs on a tape, marks symbols during multiplication, and prints each intermediate state.

Demonstrates: Vector insertion, unary encoding, marker symbols, and repeated state transitions.

## Build and run

From the repository root:

```sh
cmake -S . -B build
cmake --build build --config Release --target tape_multiplication_mt
./build/bin/tape_multiplication_mt
```

For a Visual Studio build, use `build/bin/Release/`; Windows executables end in `.exe`. See the [root build instructions](../../README.md#build-and-run).

Enter two small nonnegative integers, for example 2 and 3. The final product is the run after the final & marker. Large values produce long output. A missing-separator exception completes a previously missing return path; valid tapes follow the original algorithm.

## Targets

| Target | Source | Platform |
| --- | --- | --- |
| `tape_multiplication_mt` | `MT.cpp` | Portable |
