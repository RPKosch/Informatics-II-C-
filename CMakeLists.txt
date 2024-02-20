cmake_minimum_required(VERSION 3.24)
project(Informatics_II_Code C)

add_subdirectory("All Exercises/Exercise 1")
add_subdirectory("All Exercises/Exercise 2")

set(CMAKE_C_STANDARD 11)

add_executable(Informatics_II_Code main.c)
