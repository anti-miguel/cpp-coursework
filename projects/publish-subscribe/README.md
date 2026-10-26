# Publish/subscribe broker with threads

Concurrent programming practice (Programación Concurrente, 2025–2026). A broker, two publishers and two subscribers each run on their own thread and talk only through message queues. Subscribers register for topics; publishers send messages on a topic; the broker forwards each one to every subscriber of that topic and keeps counts. Every component shuts down cleanly on a stop message.

Demonstrates: `std::thread`, mutex-protected message queues, condition variables, message passing between threads, and orderly shutdown.

`pubsub.cpp` is the solution. `msgsbase.cpp` (message and thread-wrapper base classes) and `ConcurrenciaProfe.h` come from the course template the practice builds on.

## Build and run

From the repository root:

```sh
cmake -S . -B build
cmake --build build --config Release --target pubsub_demo
./build/bin/pubsub_demo
```

Expected ending: 9 publications received, 12 messages forwarded, and 6 messages received by each subscriber. The order of lines between threads can vary from run to run.
