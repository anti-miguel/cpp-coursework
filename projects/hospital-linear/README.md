# Hospital with linear containers

A hospital model stores medicines, doctors, patients, pending treatments, and treatment history. This is the implementation from the linear-container AED exercise.

Demonstrates: Lists, deques, stacks, priority queues, copy behavior, inventory replenishment, and recursive payment.

## Build and run

From the repository root:

```sh
cmake -S . -B build
cmake --build build --config Release --target hospital_linear
```

For a Visual Studio build, use `build/bin/Release/`; Windows executables end in `.exe`. See the [root build instructions](../../README.md#build-and-run).

This target is a static library and has no interactive main. The supplied implementation retains raw-pointer ownership, an empty discharge method, and its original patient/doctor queue semantics. The original tests cover a limited set of cases; passing them is not a full memory-safety or triage audit.

## Targets

| Target | Source | Platform |
| --- | --- | --- |
| `hospital_linear` | `lib.cpp` | Portable static library |
| `ProyectoAED1_test` | Locally obtained course test file | Optional; GoogleTest required |

## Original course tests

Obtain `ProyectoAED1_test.cpp` through the course's official distribution and place it under `_private/`. Install GoogleTest separately; its licence and sources are not part of this repository. CMake must be able to find its `GTestConfig.cmake` package.

```sh
cmake -S . -B build-tests -DCOURSE_TEST_FILE=_private/ProyectoAED1_test.cpp -DCMAKE_PREFIX_PATH=_private/gtest-install
cmake --build build-tests --config Release --target ProyectoAED1_test
ctest --test-dir build-tests -C Release -R hospital_course_tests --output-on-failure
```

Adjust the relative test path and package prefix to your local copies. Without `COURSE_TEST_FILE`, the library builds with no GoogleTest dependency. The local validation ran all seven active tests from the supplied suite successfully. The separate delivery exercise from the same source directory is in [delivery-scheduler](../delivery-scheduler/).
