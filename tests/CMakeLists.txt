# Test command line interface

add_executable(test_cli test_cli.cpp)
target_link_libraries(test_cli PRIVATE Tracey)

add_test(NAME test_cli_no_parameters COMMAND test_cli)
add_test(NAME test_cli_one_parameter COMMAND test_cli input_file)
add_test(NAME test_cli_two_parameters COMMAND test_cli input_file output_file)
add_test(NAME test_cli_three_parameters COMMAND test_cli input_file output_file output_file2)
set_property(TEST test_cli_no_parameters PROPERTY WILL_FAIL ON)
set_property(TEST test_cli_one_parameter PROPERTY WILL_FAIL ON)
set_property(TEST test_cli_three_parameters PROPERTY WILL_FAIL ON)
