/*
** EPITECH PROJECT, 2026
** rays
** File description:
** rays
*/

#include "../../include/wolf3d.h"
#include <math.h>

void create_pixel(wall_t *wall, int color,
    int index, sfUint8 *pixel)
{
    wall->pixel[index + 0] = pixel[color];
    wall->pixel[index + 1] = pixel[color + 1];
    wall->pixel[index + 2] = pixel[color + 2];
    wall->pixel[index + 3] = pixel[color + 3];
}

void create_fog_pixel(wall_t *wall, sfVector2i *index, sfUint8 *pixel,
    float fog)
{
    wall->pixel[index->y + 0] = (sfUint8)(pixel[index->x] * fog);
    wall->pixel[index->y + 1] = (sfUint8)(pixel[index->x + 1] * fog);
    wall->pixel[index->y + 2] = (sfUint8)(pixel[index->x + 2] * fog);
    wall->pixel[index->y + 3] = pixel[index->x + 3];
}
