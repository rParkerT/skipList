add_library(src INTERFACE)
target_include_directories(src INTERFACE inc/)

add_executable(skipList main.cpp)

target_link_libraries(skipList src)
