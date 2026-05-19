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

    if (wolf->settings->crosshair)
        sfRenderWindow_drawSprite(win->window, sprite, NULL);
}
