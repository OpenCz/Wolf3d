/*
** EPITECH PROJECT, 2026
** ~/EpitechProjects/Wolf3d/src/init
** File description:
** init_triangle
*/

#include "wolf3d.h"

static void set_triangle_param(triangle_t *triangle, sfVector2f *pos,
    sfVector2f points[3])
{
    sfConvexShape_setPointCount(triangle->shape, 3);
    for (int i = 0; i < 3; i++)
        sfConvexShape_setPoint(triangle->shape, i, points[i]);
    sfConvexShape_setFillColor(triangle->shape, sfColor_fromRGB(138, 2, 0));
    sfConvexShape_setPosition(triangle->shape, *pos);
}

triangle_t *create_triangle(triangle_t *data,
    sfVector2f *pos, sfVector2f points[3])
{
    triangle_t *triangle = malloc(sizeof(triangle_t));

    if (!triangle)
        return NULL;
    triangle->shape = sfConvexShape_create();
    if (!triangle->shape) {
        free(triangle);
        return NULL;
    }
    triangle->state = data->state;
    triangle->type = data->type;
    triangle->name = data->name;
    set_triangle_param(triangle, pos, points);
    return triangle;
}
