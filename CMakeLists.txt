cmake_minimum_required(VERSION 3.12)
project(cs327 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

if ($ENV{CLION_IDE})
else ()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ggdb")
endif ()

add_executable(main main.c map/map.c map/terrain.c map/roads_and_border.c map/buildings.c map/grid.c map/grid.h)
