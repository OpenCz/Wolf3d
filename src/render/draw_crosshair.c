/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** draw weapon crosshair
*/

#include "../../include/wolf3d.h"

void draw_crosshair(wolf_t *wolf, window_t *win)
{
    sfSprite *sprite = wolf->game->crosshair.cursor->sprite;
    sfVector2i pos = sfMouse_getPositionRenderWindow(win->window);
    sfVector2i center = {win->width / 2, win->height / 2};
    sfVector2i vector = {pos.x - center.x, pos.y - center.y};

    wolf->player->angle += (float)(vector.x / 200.f);
    sfMouse_setPositionRenderWindow(center, win->window);
    sfRenderWindow_drawSprite(win->window, sprite, NULL);
}
