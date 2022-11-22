add_executable(cli cli.cpp)
add_executable(box box.cpp)
target_link_libraries(cli PRIVATE Tracey)
