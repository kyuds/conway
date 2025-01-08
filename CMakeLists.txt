cmake_minimum_required(VERSION 3.15)

# Basic Setup
project(
    Conway
    VERSION 0.1
    DESCRIPTION "conway sim with ncurses tui"
    LANGUAGES C
)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# ncurses
include(FetchContent)

FetchContent_Declare(
    ncurses
    GIT_REPOSITORY https://github.com/mirror/ncurses.git
    GIT_TAG v6.4
)
FetchContent_MakeAvailable(ncurses)

# executable
add_executable(conway
    board.h
    board.c
    tui.h
    tui.c
    main.c
)

target_link_libraries(conway
    PRIVATE
        ncurses
)
