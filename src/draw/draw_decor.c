/*
** EPITECH PROJECT, 2026
** draw
** File description:
** decor
*/

#include "../../include/wolf3d.h"

void draw_floor_and_ceiling(sfRenderWindow *window)
{
    sfRectangleShape *floor = sfRectangleShape_create();
    sfRectangleShape *ceiling = sfRectangleShape_create();

    if (!floor || !ceiling)
        return;
    sfRectangleShape_setSize(floor,
        (sfVector2f){WINDOW_WIDTH, WINDOW_HEIGHT / 2});
    sfRectangleShape_setFillColor(floor, sfColor_fromRGB(100, 100, 100));
    sfRectangleShape_setPosition(floor,
        (sfVector2f){0, WINDOW_HEIGHT / 2});
    sfRenderWindow_drawRectangleShape(window, floor, NULL);
    sfRectangleShape_setSize(ceiling,
        (sfVector2f){WINDOW_WIDTH, WINDOW_HEIGHT / 2});
    sfRectangleShape_setFillColor(ceiling, sfColor_fromRGB(50, 50, 50));
    sfRectangleShape_setPosition(ceiling, (sfVector2f){0, 0});
    sfRenderWindow_drawRectangleShape(window, ceiling, NULL);
    sfRectangleShape_destroy(floor);
    sfRectangleShape_destroy(ceiling);
}
