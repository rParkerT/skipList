project(SkipList)
cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(src)
add_subdirectory(test)

add_custom_target(ALL COMMAND make run
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
)
