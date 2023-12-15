cmake_minimum_required(VERSION 3.27)
project(tetristeCLI C)

set(CMAKE_C_STANDARD 99)

add_executable(tetristeCLI
        main.c
        tetriste.c
        tetriste.h
)
