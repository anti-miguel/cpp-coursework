# Tic-tac-toe

A console grid game provides two-player turns and a basic computer-opponent mode, with a separate earlier version.

Demonstrates: Array-backed board state, move validation, win/draw checks, and randomized bot moves.

## Build and run

From the repository root:

```sh
cmake -S . -B build
cmake --build build --config Release --target tic_tac_toe_3enraya
./build/bin/tic_tac_toe_3enraya
```

For a Visual Studio build, use `build/bin/Release/`; Windows executables end in `.exe`. See the [root build instructions](../../README.md#build-and-run).

Select mode 1 for two players or mode 2 for the bot and enter board positions from 1 to 9. Mode 3 is advertised by the original menu but is not implemented. The source is kept at its coursework behavior.

## Targets

| Target | Source | Platform |
| --- | --- | --- |
| `tic_tac_toe_3enraya` | `3enraya.cpp` | Portable |
| `tic_tac_toe_early_3enraya` | `early/3enraya.cpp` | Portable |
