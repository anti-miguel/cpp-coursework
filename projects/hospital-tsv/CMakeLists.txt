add_library(hospital_tsv STATIC libtest.cpp TSVLoader.cpp)
target_include_directories(hospital_tsv PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
coursework_program(hospital_tsv_demo ProyrctoAED1test.cpp)
target_link_libraries(hospital_tsv_demo PRIVATE hospital_tsv)
