/*
** EPITECH PROJECT, 2026
** is
** File description:
** wall
*/

#include "../../include/wolf3d.h"

int is_wall(int x, int y)
{
    int tile_x;
    int tile_y;

    if (x < 0 || y < 0)
        return 1;
    tile_x = x / TILE_SIZE;
    tile_y = y / TILE_SIZE;
    if (tile_x < 0 || tile_x >= MAP_WIDTH)
        return 1;
    if (tile_y < 0 || tile_y >= MAP_HEIGHT)
        return 1;
    return map[tile_y][tile_x] == 1;
}
