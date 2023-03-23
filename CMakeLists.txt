project(cs327)
add_executable(main main.c data/heap.c entity/costs.c entity/costs.h entity/entity.c map/buildings.c map/buildings.h map/grid.c map/map.c map/roads_and_border.c map/roads_and_border.h map/terrain.c map/terrain.h)
target_link_libraries(main ncurses)
