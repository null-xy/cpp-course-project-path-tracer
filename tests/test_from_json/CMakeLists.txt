add_executable(test_from_json test_from_json.cpp)
target_link_libraries(test_from_json PRIVATE Tracey)
add_test(NAME test_from_json COMMAND test_from_json)
