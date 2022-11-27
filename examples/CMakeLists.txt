add_executable(cli cli.cpp)
target_link_libraries(cli PRIVATE Tracey)
add_executable(box box.cpp)
target_link_libraries(box PRIVATE Tracey)