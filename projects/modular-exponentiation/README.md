# Modular exponentiation

A fixed demonstration computes three modular powers using repeated squaring.

Demonstrates: Bit shifts, modular arithmetic, and logarithmic-time exponentiation.

## Build and run

From the repository root:

```sh
cmake -S . -B build
cmake --build build --config Release --target modular_exponentiation_calculadoramodulo
./build/bin/modular_exponentiation_calculadoramodulo
```

For a Visual Studio build, use `build/bin/Release/`; Windows executables end in `.exe`. See the [root build instructions](../../README.md#build-and-run).

No input is required. The supplied constants produce 735 2090 917. The helper assumes a nonzero modulus and values whose intermediate products fit unsigned long long; it is an arithmetic exercise.

## Targets

| Target | Source | Platform |
| --- | --- | --- |
| `modular_exponentiation_calculadoramodulo` | `calculadoramodulo.cpp` | Portable |
