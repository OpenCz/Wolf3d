/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** draw weapon crosshair
*/

#include "../../include/wolf3d.h"

void draw_crosshair(wolf_t *wolf, window_t *win)
{
    sfRectangleShape *shape = sfRectangleShape_create();
    float cx = win->width / 2.0f;
    float cy = win->height / 2.0f;

    (void)wolf;
    sfRectangleShape_setFillColor(shape, sfWhite);
    sfRectangleShape_setSize(shape,
        (sfVector2f){CROSSHAIR_SIZE, CROSSHAIR_THICK});
    sfRectangleShape_setPosition(shape, (sfVector2f){
        cx - CROSSHAIR_GAP - CROSSHAIR_SIZE, cy - CROSSHAIR_THICK / 2.0f});
    sfRenderWindow_drawRectangleShape(win->window, shape, NULL);
    sfRectangleShape_setPosition(shape,
        (sfVector2f){cx + CROSSHAIR_GAP, cy - CROSSHAIR_THICK / 2.0f});
    sfRenderWindow_drawRectangleShape(win->window, shape, NULL);
    sfRectangleShape_setSize(shape,
        (sfVector2f){CROSSHAIR_THICK, CROSSHAIR_SIZE});
    sfRectangleShape_setPosition(shape, (sfVector2f){
        cx - CROSSHAIR_THICK / 2.0f, cy - CROSSHAIR_GAP - CROSSHAIR_SIZE});
    sfRenderWindow_drawRectangleShape(win->window, shape, NULL);
    sfRectangleShape_setPosition(shape,
        (sfVector2f){cx - CROSSHAIR_THICK / 2.0f, cy + CROSSHAIR_GAP});
    sfRenderWindow_drawRectangleShape(win->window, shape, NULL);
    sfRectangleShape_destroy(shape);
}
