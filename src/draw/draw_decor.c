/*
** EPITECH PROJECT, 2026
** draw
** File description:
** decor
*/

#include "../../include/wolf3d.h"

void draw_floor_and_ceiling(window_t *window_data)
{
    sfRectangleShape *floor = sfRectangleShape_create();
    sfRectangleShape *ceiling = sfRectangleShape_create();

    if (!floor || !ceiling)
        return;
    sfRectangleShape_setSize(floor,
        (sfVector2f){window_data->width, window_data->height / 2});
    sfRectangleShape_setFillColor(floor, sfColor_fromRGB(100, 100, 100));
    sfRectangleShape_setPosition(floor,
        (sfVector2f){0, window_data->height / 2});
    sfRenderWindow_drawRectangleShape(window_data->window, floor, NULL);
    sfRectangleShape_setSize(ceiling,
        (sfVector2f){window_data->width, window_data->height / 2});
    sfRectangleShape_setFillColor(ceiling, sfColor_fromRGB(50, 50, 50));
    sfRectangleShape_setPosition(ceiling, (sfVector2f){0, 0});
    sfRenderWindow_drawRectangleShape(window_data->window, ceiling, NULL);
    sfRectangleShape_destroy(floor);
    sfRectangleShape_destroy(ceiling);
}
