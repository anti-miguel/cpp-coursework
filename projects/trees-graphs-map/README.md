# Trees, graphs, and hash buckets

A fixed demonstration constructs a binary tree and weighted graph, prints traversals and paths, and checks membership in a bucket-based map.

Demonstrates: Templates, parent/child pointers, BFS/DFS, minimum-weight path search, adjacency lists, and bucket hashing.

## Build and run

From the repository root:

```sh
cmake -S . -B build
cmake --build build --config Release --target structures_demo
./build/bin/structures_demo
```

For a Visual Studio build, use `build/bin/Release/`; Windows executables end in `.exe`. See the [root build instructions](../../README.md#build-and-run).

The expected minimum path is 1 3 2 4. Tree template definitions remain included from Tree.cpp, so that file is not compiled as a separate translation unit. The demonstration uses small positive edge weights and integer map keys. The byte-based map hash is an educational implementation, unsuitable for general string/object keys or persisted hashes.

## Targets

| Target | Source | Platform |
| --- | --- | --- |
| `structures_demo` | `main.cpp` | Portable |
