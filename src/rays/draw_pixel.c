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
