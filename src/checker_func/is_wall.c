/*
** EPITECH PROJECT, 2026
** is
** File description:
** wall
*/

#include "../../include/wolf3d.h"

int is_wall(wall_t *wall, int x, int y)
{
    int tile_x;
    int tile_y;
    int is_wall = 0;

    if (x < 0 || y < 0)
        return 1;
    tile_x = x / TILE_SIZE;
    tile_y = y / TILE_SIZE;
    if (tile_x < 0 || tile_x >= MAP_WIDTH)
        return 1;
    if (tile_y < 0 || tile_y >= MAP_HEIGHT)
        return 1;
    is_wall = get_map_tile(tile_x, tile_y);
    if (is_wall != 0)
        wall->wall = wall->text_arr[is_wall - 1];
    return is_wall != 0;
}
