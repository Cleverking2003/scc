cmake_minimum_required(VERSION 3.10)

project(scc)

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
add_executable(scc codegen.cpp main.cpp parser.cpp sema.cpp tokenizer.cpp)
