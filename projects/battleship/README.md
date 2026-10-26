# Battleship board prototype

A randomly generated board accepts row/column shots and displays hits and misses.

Demonstrates: Two-dimensional arrays, random placement, coordinate conversion, and board rendering.

## Build and run

From the repository root:

```sh
cmake -S . -B build
cmake --build build --config Release --target battleship_hundirlaflota
./build/bin/battleship_hundirlaflota
```

For a Visual Studio build, use `build/bin/Release/`; Windows executables end in `.exe`. See the [root build instructions](../../README.md#build-and-run).

Windows only: rendering calls the Windows console clear command. Enter row and column values from 1 to 10. The prototype loops indefinitely; use Ctrl+C to stop. It does not implement a complete fleet game.

## Targets

| Target | Source | Platform |
| --- | --- | --- |
| `battleship_hundirlaflota` | `hundirlaflota.cpp` | Windows |
