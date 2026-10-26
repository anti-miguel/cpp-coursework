# Roguelike prototypes

Several standalone console prototypes explore generated maps, movement, encounters, combat, inventories, and character progression. Each source represents a separate version.

Demonstrates: Grid-based world state, random encounters, classes/structs, combat calculations, menus, and real-time keyboard input in Windows variants.

## Build and run

From the repository root:

```sh
cmake -S . -B build
cmake --build build --config Release --target roguelike_roguelike
./build/bin/roguelike_roguelike
```

For a Visual Studio build, use `build/bin/Release/`; Windows executables end in `.exe`. See the [root build instructions](../../README.md#build-and-run).

In Roguelike.cpp use lowercase w/a/s/d for movement and q to quit. The rogue2/rogue3 variants and the early Roguelike use Windows keyboard functions and console commands, so CMake builds them only on Windows. The early Proytest variant uses standard input. Interactive combat, balancing, input recovery, and older versions are not exhaustively tested.

## Targets

| Target | Source | Platform |
| --- | --- | --- |
| `roguelike_early_proytest` | `early/Proytest.cpp` | Portable |
| `roguelike_early_rogue2` | `early/rogue2.cpp` | Windows |
| `roguelike_early_rogue3` | `early/rogue3.cpp` | Windows |
| `roguelike_early_roguelike` | `early/Roguelike.cpp` | Windows |
| `roguelike_rogue2` | `rogue2.cpp` | Windows |
| `roguelike_rogue3` | `rogue3.cpp` | Windows |
| `roguelike_roguelike` | `Roguelike.cpp` | Portable |
