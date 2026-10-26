# Validation

## Build and tests

Validated with GCC 15.1.0 for Windows, CMake 4.4.4, and Ninja.

| Check | Result |
| --- | --- |
| Fresh Release configuration with no private dependencies | Passed: 54 application executables and 2 static libraries built |
| Default Release CTest run | Passed: 2 demonstration checks |
| Debug build with the locally obtained hospital test suite and GoogleTest 1.14.0 | Passed: all targets built, including the optional test executable |
| Original `ProyectoAED1_test.cpp` suite | Passed: all 7 active tests; the suite is kept outside Git |
| CTest run with original suite enabled | Passed: 3 entries, comprising the original suite and 2 demonstration checks |
| Scripted application smoke checks | Passed: all 12 checks below |

The smoke checks covered the delivery route estimate, tree/graph output, modular exponentiation against independently computed powers, a number-file sum, five recursively paired records, terrain generation, roguelike quit, one card-game round, unary multiplication of 2 by 3, a two-player tic-tac-toe win, loading synthetic hospital records, and library catalog commands.

Smoke inputs and captured outputs remain in ignored local storage. Interactive Windows keyboard variants were compiled but not exhaustively played. MSVC and Linux were not tested. Build success and the original tests do not establish correctness or memory safety for every archived exercise; retained limitations appear in the project READMEs.

To reproduce the public checks from the repository root:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release --parallel
ctest --test-dir build -C Release --output-on-failure
```

The [hospital README](projects/hospital-linear/README.md#original-course-tests) explains how to enable the course suite without redistributing it.

## Publication audit

| Check | Result |
| --- | --- |
| Absolute Windows paths, email addresses, credential URLs, common secret assignments and token/key formats | No matches in the public tree |
| Known personal names, unrelated project references, and sample author names | Removed from the public tree and reachable commit history |
| Lecturer libraries, sample-derived fragments, assignment PDFs, original binaries, object files, and IDE state | Absent from the public tree |
| Project documentation | All 18 project folders have READMEs and CMake targets |
| Local Markdown links | All referenced files and directories exist |
| Source integrity | Copied-source hashes still match every recorded original source file |
| Git identity | Single commit under the GitHub noreply address |

The scan covered all tracked and non-ignored public files. It checked known source-specific names as well as patterns; it is not a guarantee that arbitrary unknown secrets can be recognized. No unresolved findings remain. `_private/` holds the local provenance manifest, withheld documents/tests, dependencies, logs, and review tools; it is ignored and is not part of the publishable repository.

## Delivery gate

- Hard gate PASS: the documented build and test commands succeeded; public prose contains no fabricated features, personal paths, or credential findings. Historical design claims are explicitly labeled in both card-game documents.
- Purpose gate PASS: Markdown tables map projects, targets, and validation results. No visual assets or styling were added.
- Liveliness PASS for documentation: each project names its actual algorithms, input, targets, and retained limitations. Visual dials and screen checks do not apply to this source/documentation task.
- Craftsmanship PASS: every project has build/run instructions, local documentation links resolve, original-source integrity was checked, and validation distinguishes compilation, automated checks, and untested behavior.
