# Library catalog

An interactive catalog manages books, journals, theses, users, loans, returns, reservations, and TSV persistence.

Demonstrates: Inheritance and virtual methods, vectors, maps, priority queues, linked history, date handling, command parsing, and serialization.

## Build and run

From the repository root:

```sh
cmake -S . -B build
cmake --build build --config Release --target library_catalog
./build/bin/library_catalog
```

For a Visual Studio build, use `build/bin/Release/`; Windows executables end in `.exe`. See the [root build instructions](../../README.md#build-and-run).

Enter help for commands and exit to quit. Command arguments such as titles and user labels cannot contain spaces. Persistence writes to a relative filename, defaulting to biblioteca.tsv; choose a disposable working directory for experiments. Raw-pointer ownership and limited validation are preserved.

## Targets

| Target | Source | Platform |
| --- | --- | --- |
| `library_catalog` | `biblioteca.cpp Core.cpp Item.cpp User.cpp TSVSerializer.cpp` | Portable |
