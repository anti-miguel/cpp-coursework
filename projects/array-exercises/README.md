# Array exercises

Short programs for random integer sequences, forward and reverse traversal, tables, and two-dimensional arrays.

Demonstrates: Fixed-size arrays, indexing, random numbers, loop bounds, and formatted output.

## Build and run

From the repository root:

```sh
cmake -S . -B build
cmake --build build --config Release --target array_exercises_20de1al10enarray
./build/bin/array_exercises_20de1al10enarray
```

For a Visual Studio build, use `build/bin/Release/`; Windows executables end in `.exe`. See the [root build instructions](../../README.md#build-and-run).

These are early exercises. Some variants do not fully initialize arrays or validate requested sizes. Stay within the declared array sizes; the older variants are retained for study.

## Targets

| Target | Source | Platform |
| --- | --- | --- |
| `array_exercises_20de1al10enarray` | `20de1al10enarray.cpp` | Portable |
| `array_exercises_early_arrays_arrays2d` | `early/arrays/arrays2d.cpp` | Portable |
| `array_exercises_early_arrays_random10array` | `early/arrays/random10array.cpp` | Portable |
| `array_exercises_early_tablanaleatorios` | `early/TablaNaleatorios.cpp` | Portable |
| `array_exercises_n_numerosarray` | `n.numerosarray.cpp` | Portable |
| `array_exercises_nhasta0rachacreciente` | `Nhasta0rachacreciente.cpp` | Portable |
| `array_exercises_nhasta0y0hastan` | `Nhasta0y0hastaN.cpp` | Portable |
| `array_exercises_tablanaleatorios` | `TablaNaleatorios.cpp` | Portable |
