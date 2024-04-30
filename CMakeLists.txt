cmake_minimum_required(VERSION 3.24)
project(Informatics_II_Code C)

add_subdirectory("All Exercises/Exercise 1")
add_subdirectory("All Exercises/Exercise 2")
add_subdirectory("All Exercises/Exercise 3")
add_subdirectory("All Exercises/Exercise 4")
add_subdirectory("All Exercises/Exercise 5")
add_subdirectory("All Exercises/Exercise 6")
add_subdirectory("All Exercises/Exercise 7")
add_subdirectory("All Exercises/Exercise 8")
add_subdirectory("All Exercises/Exercise 9")

set(CMAKE_C_STANDARD 11)

add_executable(Informatics_II_Code main.c)
