find_package(Threads REQUIRED)
coursework_program(pubsub_demo pubsub.cpp)
target_link_libraries(pubsub_demo PRIVATE Threads::Threads)
if(BUILD_TESTING)
    add_test(NAME pubsub_demo_smoke COMMAND pubsub_demo)
    set_tests_properties(pubsub_demo_smoke PROPERTIES
        PASS_REGULAR_EXPRESSION "messages forwarded: 12" TIMEOUT 30)
endif()
