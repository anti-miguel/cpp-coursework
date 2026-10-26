# Programming fundamentals

Independent exercises cover variables, profile input, grades, number classification, arithmetic, loops, and a simulated account menu.

Demonstrates: Console streams, branches, loop forms, arithmetic, and simple local state.

## Build and run

From the repository root:

```sh
cmake -S . -B build
cmake --build build --config Release --target fundamentals_variables
./build/bin/fundamentals_variables
```

For a Visual Studio build, use `build/bin/Release/`; Windows executables end in `.exe`. See the [root build instructions](../../README.md#build-and-run).

Each source has its own main function and target. These early exercises preserve incomplete logic: for example, one odd-number loop has a false initial condition, and some prime/input checks are partial. The account example is a classroom simulation. Use valid numeric input; some programs require Ctrl+C to stop.

## Targets

| Target | Source | Platform |
| --- | --- | --- |
| `fundamentals_conditionals_2numerosescoger` | `conditionals/2numerosescoger.cpp` | Portable |
| `fundamentals_conditionals_adivinarnumeros` | `conditionals/adivinarnumeros.cpp` | Portable |
| `fundamentals_conditionals_compra` | `conditionals/compra.cpp` | Portable |
| `fundamentals_conditionals_numero_par_impar` | `conditionals/numero-par-impar.cpp` | Portable |
| `fundamentals_conditionals_numimpares1a100` | `conditionals/numimpares1a100.cpp` | Portable |
| `fundamentals_conditionals_test` | `conditionals/test.cpp` | Portable |
| `fundamentals_conditionals_todo` | `conditionals/TODO.cpp` | Portable |
| `fundamentals_for_loops_cuadradosycubos` | `for-loops/cuadradosycubos.cpp` | Portable |
| `fundamentals_for_loops_divisores` | `for-loops/divisores.cpp` | Portable |
| `fundamentals_grades` | `grades.cpp` | Portable |
| `fundamentals_loops_100a0` | `loops/100a0.cpp` | Portable |
| `fundamentals_loops_cuentabancaria` | `loops/cuentabancaria.cpp` | Portable |
| `fundamentals_loops_numimpares1a100` | `loops/numimpares1a100.cpp` | Portable |
| `fundamentals_loops_pedirhasta0` | `loops/Pedirhasta0.cpp` | Portable |
| `fundamentals_loops_pedirhastamedia` | `loops/Pedirhastamedia.cpp` | Portable |
| `fundamentals_loops_pedirnumerouser` | `loops/Pedirnumerouser.cpp` | Portable |
| `fundamentals_loops_pedirydivisores` | `loops/Pedirydivisores.cpp` | Portable |
| `fundamentals_loops_pediryprimos` | `loops/Pediryprimos.cpp` | Portable |
| `fundamentals_profile_input` | `profile-input.cpp` | Portable |
| `fundamentals_variables` | `variables.cpp` | Portable |
