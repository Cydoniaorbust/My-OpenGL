cmake_minimum_required(VERSION 3.0)
project(NewGame)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_subdirectory(deps/CWGE)

set(SRC src/Source.cpp)
add_executable(NewGame ${SRC})

target_link_libraries(NewGame CWGE)

target_include_directories(NewGame PUBLIC deps/CWGE/include)
target_include_directories(NewGame PUBLIC include)