/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** map
*/

#include "../include/wolf3d.h"

int get_map_tile(int tile_x, int tile_y)
{
    static const int map_data[MAP_HEIGHT][MAP_WIDTH] = {
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 2, 0, 0, 0, 1},
        {1, 0, 0, 2, 0, 2, 0, 1},
        {1, 0, 0, 0, 0, 2, 0, 1},
        {1, 0, 2, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1}
    };

    return map_data[tile_y][tile_x];
}
