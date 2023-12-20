cmake_minimum_required(VERSION 3.27)
project(tetriste C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Adding Raylib
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(
        raylib
        GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
        GIT_TAG "master"
        GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib)

# Create executable
add_executable(tetriste
        main.c

        src/tetriste.c
        src/tetriste.h

        src/cli/tetriste_cli.c
        src/cli/tetriste_cli.h

        src/gui/tetriste_gui.c
        src/gui/tetriste_gui.h

        src/gui/audio/audio.c
        src/gui/audio/audio.h

        src/gui/screens/screen_gameplay.c
        src/gui/screens/screen_title.c
        src/gui/screens/screens.h
)

target_link_libraries(tetriste raylib)

# Copy assets to build directory
add_custom_command(
        TARGET tetriste POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)