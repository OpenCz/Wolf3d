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

    if (monster->type != ENNEMY || draw->transform.y <= 0 ||
        shot < draw->drawStart.x || shot > draw->drawEnd.x)
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
        if (weapon->current_ammo <= 0)
            return;
        game->has_shot = 1;
        sfClock_restart(weapon->cd);
        weapon->current_ammo -= 1;
    }
}

int apply_frame(weapon_t *weapon, float elapsed, float frame, int rect_left)
{
    if (elapsed < frame) {
        weapon->rect.left = rect_left;
        sfSprite_setTextureRect(weapon->entity->sprite, weapon->rect);
        return 1;
    }
    return 0;
}

void animate_shot(weapon_t *weapon)
{
    float elapsed = sfTime_asSeconds(sfClock_getElapsedTime(weapon->cd));

    if (apply_frame(weapon, elapsed, 0.1, 400) ||
        apply_frame(weapon, elapsed, 0.2, 800) ||
        apply_frame(weapon, elapsed, 0.3, 1200))
        return;
    weapon->rect.left = 0;
    sfSprite_setTextureRect(weapon->entity->sprite, weapon->rect);
}

void draw_weapon(wolf_t *wolf, window_t *win, weapon_t *weapon)
{
    (void)wolf;
    animate_shot(weapon);
    sfRenderWindow_drawSprite(win->window, weapon->entity->sprite, NULL);
}
