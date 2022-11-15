add_executable(test_material test_material.cpp)
target_link_libraries(test_material PRIVATE Tracey)
add_test(NAME test_material COMMAND test_material)
