/*
** EPITECH PROJECT, 2026
** weapon
** File description:
** weapon
*/

#include "../../../include/wolf3d.h"
#include <math.h>


void draw_weapon(window_t *win, weapon_t *weapon)
{
    sfRenderWindow_drawSprite(win->window, weapon->entity->sprite, NULL);
}
