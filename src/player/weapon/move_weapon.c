/*
** EPITECH PROJECT, 2026
** main
** File description:
** main
*/

#include "../../../include/wolf3d.h"

void animate_weapon_walk(wolf_t *wolf, window_t *win, weapon_t *weapon)
{
    float time =
        sfTime_asSeconds(sfClock_getElapsedTime(wolf->game->clock[GLOBAL]));
    float x = sinf(time * 5.f) * 20.f;
    float y = fabsf(sinf(time * 5.f)) * 10.f;

    sfSprite_setPosition(weapon->entity->sprite,
        (sfVector2f){win->width / 2 + x, win->height + y});
}
