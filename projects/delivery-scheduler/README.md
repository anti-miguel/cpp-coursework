# Delivery scheduler

A fixed demonstration registers orders and couriers, prepares orders in arrival order, and assigns a route from urgent requests.

Demonstrates: Deque-based FIFO processing, priority queues, maps, sorting, optional results, and estimated route duration.

## Build and run

From the repository root:

```sh
cmake -S . -B build
cmake --build build --config Release --target delivery_demo
./build/bin/delivery_demo
```

For a Visual Studio build, use `build/bin/Release/`; Windows executables end in `.exe`. See the [root build instructions](../../README.md#build-and-run).

The demo uses neutral placeholder labels and requires no input or files. Its assigned route contains two orders with a total estimate of 53 minutes. This is an in-memory exercise.

## Targets

| Target | Source | Platform |
| --- | --- | --- |
| `delivery_demo` | `parte2_demo.cpp parte2.cpp` | Portable |
