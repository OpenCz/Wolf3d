/*
** EPITECH PROJECT, 2026
** weapon
** File description:
** weapon
*/

#include "../../../include/wolf3d.h"
#include <math.h>


void damage_monster(weapon_t *weapon, window_t *win,
    player_draw_t *draw, player_t *monster)
{
    int shot = win->width / 2;

    if (monster->type != ENNEMY || shot < draw->drawStart.x ||
        shot > draw->drawEnd.x)
        return;
    monster->hp -= weapon->damage;
    if (monster->hp <= 0) {
        monster->alive = sfFalse;
    }
}

void use_weapon(game_t *game, weapon_t *weapon)
{
    if (sfMouse_isButtonPressed(sfMouseLeft) && sfTime_asSeconds(
            sfClock_getElapsedTime(weapon->cd)) > weapon->attack_speed) {
        game->has_shot = 1;
        sfClock_restart(weapon->cd);
    }
}

void draw_weapon(window_t *win, weapon_t *weapon)
{
    sfRenderWindow_drawSprite(win->window, weapon->entity->sprite, NULL);
}
