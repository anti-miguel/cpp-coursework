coursework_program(delivery_demo parte2_demo.cpp parte2.cpp)
if(BUILD_TESTING)
    add_test(NAME delivery_demo_smoke COMMAND delivery_demo)
    set_tests_properties(delivery_demo_smoke PROPERTIES
        PASS_REGULAR_EXPRESSION "minutos=53" TIMEOUT 30)
endif()
