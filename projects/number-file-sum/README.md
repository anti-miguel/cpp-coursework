# Number-file sum

Reads numeros.txt from the current working directory, trims surrounding whitespace, and sums whitespace-separated integer tokens.

Demonstrates: File streams, string streams, trimming, iteration, and integer conversion.

## Build and run

From the repository root:

```sh
cmake -S . -B build
cmake --build build --config Release --target number_file_sum_leernumerosysuma
./build/bin/number_file_sum_leernumerosysuma
```

For a Visual Studio build, use `build/bin/Release/`; Windows executables end in `.exe`. See the [root build instructions](../../README.md#build-and-run).

Create your own numeros.txt before running, for example a line containing 1 2 3; the result is 6. No input data is copied. Missing files currently produce a zero total, malformed tokens can throw, and totals must fit int.

## Targets

| Target | Source | Platform |
| --- | --- | --- |
| `number_file_sum_leernumerosysuma` | `leernumerosysuma.cpp` | Portable |
