cmake_minimum_required(VERSION 3.17)
project(DinoCPP)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(DinoCPP main.cpp)

target_link_libraries(DinoCPP sfml-graphics sfml-window sfml-system)

set(EXECUTABLE_OUTPUT_PATH "../bin")