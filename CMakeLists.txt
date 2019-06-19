cmake_minimum_required(VERSION 3.13)
project(cppg)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
    src/cppg.cpp
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
    absl::span
)

add_subdirectory(external)
