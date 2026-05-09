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
    if (!weapon->reloading && sfKeyboard_isKeyPressed(sfKeyR) &&
        sfTime_asSeconds(sfClock_getElapsedTime(weapon->cd)) >
        weapon->attack_speed) {
        weapon->reloading = 1;
        sfClock_restart(weapon->cd);
    }
    if (weapon->reloading == 1)
        return;
    if (sfMouse_isButtonPressed(sfMouseLeft) && sfTime_asSeconds(
            sfClock_getElapsedTime(weapon->cd)) > weapon->attack_speed) {
        if (weapon->current_ammo <= 0)
            return;
        game->has_shot = 1;
        sfClock_restart(weapon->cd);
        weapon->current_ammo -= 1;
    }
}

static int apply_frame(weapon_t *weapon,
    float elapsed, float frame, int rect_left)
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

void reload_weapon(window_t *win, weapon_t *weapon)
{
    float elapsed = sfTime_asSeconds(sfClock_getElapsedTime(weapon->cd));
    sfVector2f pos = sfSprite_getPosition(weapon->entity->sprite);

    if (elapsed < 1.5f) {
        sfSprite_setPosition(weapon->entity->sprite,
            (sfVector2f){pos.x, win->height + (win->height / 2) *
                (elapsed / 1.5f)});
    } else if (elapsed < 3.f) {
        sfSprite_setPosition(weapon->entity->sprite,
            (sfVector2f){pos.x, win->height + (win->height / 2) * (1.f -
                    (elapsed - 1.5f) / 1.5f)});
    } else {
        sfSprite_setPosition(weapon->entity->sprite,
            (sfVector2f){pos.x, win->height});
        weapon->reloading = 0;
        weapon->current_ammo = weapon->max_ammo;
    }
}

void draw_weapon(wolf_t *wolf, window_t *win, weapon_t *weapon)
{
    if (weapon->reloading)
        reload_weapon(wolf->window_data, weapon);
    else
        animate_shot(weapon);
    if (!weapon->reloading && (sfKeyboard_isKeyPressed(sfKeyQ) ||
            sfKeyboard_isKeyPressed(sfKeyD) || sfKeyboard_isKeyPressed(sfKeyZ)
            || sfKeyboard_isKeyPressed(sfKeyS)))
        animate_weapon_walk(wolf, wolf->window_data, weapon);
    else if (!weapon->reloading)
        sfSprite_setPosition(weapon->entity->sprite,
            (sfVector2f){win->width / 2, win->height});
    sfRenderWindow_drawSprite(win->window, weapon->entity->sprite, NULL);
}
