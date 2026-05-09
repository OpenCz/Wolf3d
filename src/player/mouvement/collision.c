/*
** EPITECH PROJECT, 2026
** main
** File description:
** main
*/

#include "../../../include/wolf3d.h"

int check_collision(wall_t *wall, float x, float y)
{
    float min = WALL_MIN_DISTANCE;

    return is_wall(wall, (int)((x - min)), (int)((y - min))) ||
        is_wall(wall, (int)((x + min)), (int)((y - min))) ||
        is_wall(wall, (int)((x - min)), (int)((y + min))) ||
        is_wall(wall, (int)((x + min)), (int)((y + min)));
}
