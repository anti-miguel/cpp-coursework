# Character sheets

Console character builders combine an origin and profession with generated or adjusted statistics. Distinct earlier versions are retained.

Demonstrates: Stat tables, menus, random generation, and struct/class-based character state.

## Build and run

From the repository root:

```sh
cmake -S . -B build
cmake --build build --config Release --target character_sheet_ficharol
./build/bin/character_sheet_ficharol
```

For a Visual Studio build, use `build/bin/Release/`; Windows executables end in `.exe`. See the [root build instructions](../../README.md#build-and-run).

Follow the numbered origin and profession prompts. The early class-based variant is Windows only because it clears the console. Input recovery and balancing remain as in the coursework.

## Targets

| Target | Source | Platform |
| --- | --- | --- |
| `character_sheet_early_ficharol` | `early/FICHAROL.cpp` | Portable |
| `character_sheet_early_test2` | `early/test2.cpp` | Windows |
| `character_sheet_ficharol` | `ficharol.cpp` | Portable |
