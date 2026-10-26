# Hospital TSV application

A separate hospital implementation loads medicines, diseases, doctors, and patients from a tab-separated file, then demonstrates stock replenishment, treatment, and payment.

Demonstrates: TSV parsing, validation messages, entity lookup, queues, priority ordering, and recursion.

## Build and run

From the repository root:

```sh
cmake -S . -B build
cmake --build build --config Release --target hospital_tsv_demo
./build/bin/hospital_tsv_demo input.tsv
```

For a Visual Studio build, use `build/bin/Release/`; Windows executables end in `.exe`. See the [root build instructions](../../README.md#build-and-run).

Provide your own synthetic input file. No source dataset is redistributed. The common sources in ProyectoAED1 and ProyectoAED2 are consolidated here. The corrected header matches the supplied AED2 header: the stray punctuation and duplicate inline priority method have been removed. This model is separate from hospital-linear and does not use its test API.

## Targets

| Target | Source | Platform |
| --- | --- | --- |
| `hospital_tsv_demo` | `ProyrctoAED1test.cpp` | Portable |

## Input format

Each record uses tab separators. Use neutral labels and synthetic values; the following describes fields rather than supplying a dataset:

| Record | Fields after the record type |
| --- | --- |
| `MED` | integer ID, label, type, quantity |
| `ENF` | integer ID, label, lethality, urgency |
| `DOC` | integer ID, label, initial payment total |
| `PAC` | integer ID, label, semicolon-separated disease IDs |

Blank lines and lines starting with `#` are ignored. Patient references are resolved after loading the disease definitions. The input filename is the first argument; without it, the program tries `datos_mix.tsv` in the current directory.
