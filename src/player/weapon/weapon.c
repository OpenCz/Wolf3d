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

    if ((monster->type != GARBAGE_T || weapon->type != GUN) &&
        (monster->type != ENNEMY || draw->transform.y <= 0 ||
            draw->sprite_width <= 0 || draw->sprite_height <= 0))
        return;
    if (shot < draw->drawStart.x || shot > draw->drawEnd.x)
        return;
    if ((monster->type == GARBAGE_T && draw->distance > 3) ||
        (weapon->type == SHOTGUN && draw->distance > 8))
        return;
    monster->hp -= weapon->damage;
    if (monster->hp <= 0) {
        monster->alive = sfFalse;
    }
}

void use_weapon(game_t *game, weapon_t *weapon)
{
    if (!weapon)
        return;
    if (!weapon->reloading && sfKeyboard_isKeyPressed(sfKeyR) &&
        sfTime_asSeconds(sfClock_getElapsedTime(weapon->cd)) >
        weapon->attack_speed && weapon->type == GUN) {
        weapon->reloading = 1;
        weapon->rect.left = 0;
        sfSprite_setTextureRect(weapon->entity->sprite, weapon->rect);
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

int animate_shot(weapon_t *weapon, sfVector2f *rect_1,
    sfVector2f *rect_2, sfVector2f *rect_3)
{
    float elapsed = sfTime_asSeconds(sfClock_getElapsedTime(weapon->cd));

    if (apply_frame(weapon, elapsed, rect_1->x, rect_1->y) ||
        apply_frame(weapon, elapsed, rect_2->x, rect_2->y) ||
        apply_frame(weapon, elapsed, rect_3->x, rect_3->y))
        return 0;
    weapon->rect.left = 0;
    sfSprite_setTextureRect(weapon->entity->sprite, weapon->rect);
    return 1;
}

static void shot_weapon(weapon_t *w)
{
    float elapsed = sfTime_asSeconds(sfClock_getElapsedTime(w->cd));
    float end_frame = w->type == GUN ? 0.3 : 0.6;

    if (w->type == SHOTGUN || w->type == VACUUM) {
        if (elapsed >= end_frame) {
            w->reloading = 1;
            return;
        }
    }
    animate_shot(w, &(sfVector2f){w->type == GUN ? 0.1 : 0.2, 400},
        &(sfVector2f){w->type == GUN ? 0.2 : 0.4, 800},
        &(sfVector2f){w->type == GUN ? 0.3 : 0.6, 1200});
}

static void reload_gun(sfVector2f *pos, window_t *win,
    weapon_t *weapon, float elapsed)
{
    if (elapsed < 0.8) {
        sfSprite_setPosition(weapon->entity->sprite,
            (sfVector2f){pos->x, win->height + (win->height / 2) *
                (elapsed / 0.8)});
    } else if (elapsed < 1.6f) {
        sfSprite_setPosition(weapon->entity->sprite,
            (sfVector2f){pos->x, win->height + (win->height / 2) * (1.f -
                    (elapsed - 0.8) / 0.8)});
    } else {
        sfSprite_setPosition(weapon->entity->sprite,
            (sfVector2f){pos->x, win->height});
        weapon->reloading = 0;
        weapon->current_ammo = weapon->max_ammo;
    }
}

static void reload_shotgun(weapon_t *weapon, float elapsed)
{
    if (elapsed >= 0.6 && elapsed <= 1.6)
        animate_shot(weapon, &(sfVector2f){0.8, 1600},
            &(sfVector2f){1.2, 2000}, &(sfVector2f){1.4, 2400});
    else {
        weapon->reloading = 0;
        weapon->current_ammo = weapon->max_ammo;
    }
}

void reload_weapon(window_t *win, weapon_t *weapon)
{
    float elapsed = sfTime_asSeconds(sfClock_getElapsedTime(weapon->cd));
    sfVector2f pos = sfSprite_getPosition(weapon->entity->sprite);

    switch (weapon->type){
        case GUN:
            reload_gun(&pos, win, weapon, elapsed);
            break;
        case SHOTGUN:
        case VACUUM:
            reload_shotgun(weapon, elapsed);
            break;
        default:
            break;
    }
}

void draw_weapon(wolf_t *wolf, window_t *win, weapon_t *w)
{
    if (!w)
        return;
    if (wolf->game->inv.open)
        return sfRenderWindow_drawSprite(win->window,
            w->entity->sprite, NULL);
    if (w->reloading)
        reload_weapon(wolf->window_data, w);
    else
        shot_weapon(w);
    if (!w->reloading &&
        (sfKeyboard_isKeyPressed(sfKeyQ) ^ sfKeyboard_isKeyPressed(sfKeyD) ||
            sfKeyboard_isKeyPressed(sfKeyZ) ^ sfKeyboard_isKeyPressed(sfKeyS)))
        animate_weapon_walk(wolf, wolf->window_data, w);
    else if (!w->reloading)
        sfSprite_setPosition(w->entity->sprite,
            (sfVector2f){win->width / 2, win->height});
    sfRenderWindow_drawSprite(win->window, w->entity->sprite, NULL);
}
