coursework_program(structures_demo main.cpp)
if(BUILD_TESTING)
    add_test(NAME structures_demo_smoke COMMAND structures_demo)
    set_tests_properties(structures_demo_smoke PROPERTIES
        PASS_REGULAR_EXPRESSION "Minimum path from 1 to 4: 1 3 2 4" TIMEOUT 30)
endif()
