cmake_minimum_required(VERSION 3.12)
project(cs327 C)
set(CMAKE_C_STANDARD 11)

if ($ENV{CLION_IDE})
else ()
    set(CMAKE_C_COMPILER "gcc")
    set(CMAKE_CXX_COMPILER "g++")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ggdb")
endif ()

add_executable(main datastructures/testfibheap.c map/map.c map/map.h map/terrain.c map/terrain.h map/roads_and_border.c map/roads_and_border.h map/buildings.c map/buildings.h map/grid.c map/grid.h entity/entity.c entity/entity.h entity/costs.c entity/costs.h entity/move.c entity/move.h datastructures/fibheap.c datastructures/fibheap.h)
target_link_libraries(main m)
