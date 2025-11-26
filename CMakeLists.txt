cmake_minimum_required(VERSION 4.0)
project(P1_Product C)

set(CMAKE_C_STANDARD 11)

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

add_executable(P1_Product src/main.c
        src/ReadMapFromFile.c
        src/ReadMapFromFile.h
        src/CreateVisualMap.c
        src/CreateVisualMap.h
        src/RobotStruct.h
        src/RobotStruct.c)

target_link_libraries(P1_Product raylib)

add_subdirectory(src)

