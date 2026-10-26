# Random terrain

Two small console demonstrations fill a grid with random terrain tiles and display the generated map.

Demonstrates: Nested containers, random tile selection, iteration, and text rendering.

## Build and run

From the repository root:

```sh
cmake -S . -B build
cmake --build build --config Release --target random_terrain_randomterrain
./build/bin/random_terrain_randomterrain
```

For a Visual Studio build, use `build/bin/Release/`; Windows executables end in `.exe`. See the [root build instructions](../../README.md#build-and-run).

The map is generated at runtime; no external map or asset files are required. The early variant is kept separately because its source differs.

## Targets

| Target | Source | Platform |
| --- | --- | --- |
| `random_terrain_early_randomterrain` | `early/randomterrain.cpp` | Portable |
| `random_terrain_randomterrain` | `randomterrain.cpp` | Portable |
