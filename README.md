# C++ coursework and small games

University exercises and personal console games, from loops and arrays to container-based applications, trees, graphs, and file serialization. Each application has its own executable. The original Spanish identifiers and prompts are retained.

These are coursework snapshots. Compilation fixes, UTF-8 normalization, and privacy edits are deliberately small; game rules and unfinished exercise behavior are preserved. Earlier variants live in `early/` where they differ from the later source.

## Projects

| Project | What it demonstrates | Platform |
| --- | --- | --- |
| [Seven and a half](projects/seven-and-a-half/) | Decks, structs, shuffling, player turns | Portable console |
| [Roguelike prototypes](projects/roguelike/) | Tile maps, combat, inventories, character progression | Mixed; real-time variants require Windows |
| [Character sheets](projects/character-sheet/) | Menu input, stat tables, character construction | Mixed |
| [Tic-tac-toe](projects/tic-tac-toe/) | Grid state, win detection, player and bot turns | Portable console |
| [Battleship](projects/battleship/) | Random board generation and coordinate input | Windows console |
| [Sliding puzzles](projects/sliding-puzzle/) | Shuffling, grid movement, adjacency checks | Portable console |
| [Random terrain](projects/random-terrain/) | Procedural tile generation | Portable console |
| [Hospital: linear containers](projects/hospital-linear/) | Lists, stacks, queues, stock calculations, recursive payment | Portable library |
| [Hospital: TSV application](projects/hospital-tsv/) | File parsing, entity relationships, triage workflow | Portable console |
| [Delivery scheduler](projects/delivery-scheduler/) | FIFO preparation, urgent orders, route assignment | Portable console |
| [Library catalog](projects/library-catalog/) | Inheritance, loans, reservations, TSV persistence, command parsing | Portable console |
| [Trees, graphs, and map](projects/trees-graphs-map/) | Tree traversals, weighted paths, hash buckets | Portable console |
| [Publish/subscribe broker](projects/publish-subscribe/) | Threads, message queues, topic routing, clean shutdown | Portable console |
| [Tape multiplication](projects/tape-multiplication/) | Unary representation and tape-state transitions | Portable console |
| [Modular exponentiation](projects/modular-exponentiation/) | Exponentiation by squaring | Portable console |
| [Array exercises](projects/array-exercises/) | Random sequences, traversal, multidimensional arrays | Portable console |
| [Fundamentals](projects/fundamentals/) | Variables, conditionals, loops, arithmetic, console input | Portable console |
| [Recursive pairs](projects/recursive-pairs/) | Recursive traversal and pairing parallel arrays | Portable console |
| [Number-file sum](projects/number-file-sum/) | Text files, whitespace trimming, numeric conversion | Portable console |

## Build and run

Requires CMake 3.20 or newer and a C++20 compiler. Build from the repository root:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release --parallel
ctest --test-dir build -C Release --output-on-failure
```

For GCC on Windows, use a terminal with `g++` and Ninja on `PATH` and add `-G Ninja` to the configure command. MinGW executables link their runtime statically. For MSVC, use a Visual Studio developer terminal and its default CMake generator.

Executables go in `build/bin/`. Visual Studio and other multi-configuration generators add the configuration, for example `build/bin/Release/`. Windows executables have an `.exe` suffix. A project README lists every target and its source:

```sh
cmake --build build --config Release --target structures_demo
./build/bin/structures_demo
```

On other operating systems, CMake omits the seven targets that use Windows console input or shell commands. They are marked in their project READMEs. Portability is based on source inspection; the recorded build used GCC on Windows. MSVC and Linux have not been tested.

## Tests and limitations

The default CTest run checks the delivery demo's route estimate and the graph demo's minimum path. The original `ProyectoAED1_test.cpp` suite can be enabled with a locally obtained copy and an installed GoogleTest package; see [hospital test instructions](projects/hospital-linear/README.md).

[VALIDATION.md](VALIDATION.md) records the build, original test results, smoke checks, and publication audit. Compilation does not establish correctness for every archived exercise. Some interactive prototypes lack input recovery or a normal exit command; use small, valid inputs and Ctrl+C where necessary. Known project-specific issues are documented beside their code.

## Source selection and redistribution

The public tree contains the selected student implementations and the card game's historical Markdown design and presentation. Identical source files have been consolidated. The original source locations remain untouched.

The following material stays outside Git in `_private/` for local review:

| Material | Reason | How to obtain it |
| --- | --- | --- |
| Assignment statements, including the linear AED statement and library assignment PDF | Course documents without redistribution permission | Obtain through the course's official distribution |
| Original hospital course tests and placeholder test scaffolding | Lecturer-provided or uncertain authorship | Obtain through the course; supply the test path to CMake |
| Review header and `TestTest.cpp` copies from `CodigoRepaso` and the standalone source | Lecturer-authored exercises and tests; no student implementation was supplied | Obtain through the course if studying that material separately |
| `ThreadsEntornosClean.cpp` | Sample-derived teaching material; independent student authorship is unclear | Obtain the original teaching sample through the course |
| `VirtualCable.cpp` | Declared sample-derived driver fragment, missing headers and unclear redistribution basis | Consult the upstream SDK sample and its licence separately |
| Tic-tac-toe correction source | Authorship of the correction is unclear | Confirm permission with the course before reusing it |
| Card presentation PDF | Binary export withheld from publication; the reviewable Markdown is included | Export the included Markdown if a PDF is needed |

No lecturer libraries, datasets, original executables, object files, IDE state, or unrelated sources are included. The supplied hospital implementations and graph/tree implementation are self-contained and do not require excluded lecturer libraries. The review-only material is not a build dependency of the public targets. No licence grant is inferred for excluded material.
