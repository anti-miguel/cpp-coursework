# Sliding-puzzle prototypes

Two 3x3 number puzzles shuffle tiles and move a selected neighboring tile into the blank square.

Demonstrates: Random shuffling, two-dimensional coordinates, adjacency checks, and board rendering.

## Build and run

From the repository root:

```sh
cmake -S . -B build
cmake --build build --config Release --target sliding_puzzle_examen
./build/bin/sliding_puzzle_examen
```

For a Visual Studio build, use `build/bin/Release/`; Windows executables end in `.exe`. See the [root build instructions](../../README.md#build-and-run).

Select a numbered tile adjacent to the blank. Random shuffles can produce unsolvable boards. The examentest prototype has no win/exit condition; use Ctrl+C to stop. Input recovery is limited. A forward declaration fixes its original call-before-declaration build error.

## Targets

| Target | Source | Platform |
| --- | --- | --- |
| `sliding_puzzle_examen` | `examen.cpp` | Portable |
| `sliding_puzzle_examentest` | `examentest.cpp` | Portable |
