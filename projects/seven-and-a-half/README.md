# Las Siete y Media

A Spanish-language console card-game prototype shuffles a 40-card deck and runs player turns followed by an automated bank turn.

Demonstrates: Structs, a fixed-size deck, shuffling, vectors of players, stream operators, and turn sequencing.

## Build and run

From the repository root:

```sh
cmake -S . -B build
cmake --build build --config Release --target seven_and_a_half_7_5
./build/bin/seven_and_a_half_7_5
```

For a Visual Studio build, use `build/bin/Release/`; Windows executables end in `.exe`. See the [root build instructions](../../README.md#build-and-run).

The source stores integer scores and assigns cards values 1 through 10. It therefore does not implement traditional half-point face-card scoring. Deck exhaustion and player-count validation are also incomplete. Use a small positive player count and follow the s/n prompts. These behaviors are preserved rather than changed into a new game.

## Targets

| Target | Source | Platform |
| --- | --- | --- |
| `seven_and_a_half_7_5` | `7.5.cpp` | Portable |

## Historical documents

[doc.md](doc.md) and [pre.md](pre.md) preserve the supplied Spanish design document and presentation script. They describe a broader modular design, fractional scoring, and visual features that are absent from this source snapshot. Their historical status is stated at the top of each file. The PDF export is withheld from Git.
