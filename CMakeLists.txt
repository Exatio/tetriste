cmake_minimum_required(VERSION 3.27)
project(tetristeCLI C)

set(CMAKE_C_STANDARD 11)

add_executable(tetriste
        src/main.c

        src/tetriste.c
        src/tetriste.h

        src/cli/tetriste_cli.c
        src/cli/tetriste_cli.h
)
