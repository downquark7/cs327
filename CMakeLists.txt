cmake_minimum_required(VERSION 3.12)
project(cs327 C)

set(CMAKE_C_STANDARD 11)
add_executable(main main.c map/map.c map/terrain.c map/roads_and_border.c map/buildings.c map/buildings.h)
