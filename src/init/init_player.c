/*
** EPITECH PROJECT, 2026
** init
** File description:
** player
*/

#include "../../include/wolf3d.h"
#include <math.h>

static weapon_t *init_weapon(wp_type_t type, int damage,
    int max_ammo, entity_t *entity)
{
    weapon_t *weapon = calloc(1, sizeof(weapon_t));

    if (!weapon)
        return NULL;
    weapon->type = type;
    weapon->attack_speed = 1;
    weapon->current_ammo = max_ammo;
    weapon->max_ammo = max_ammo;
    weapon->damage = damage;
    weapon->cd = sfClock_create();
    weapon->entity = entity;
    weapon->rect = (sfIntRect){0, 0, 400, 600};
    sfSprite_setTextureRect(entity->sprite, weapon->rect);
    sfSprite_setOrigin(entity->sprite, (sfVector2f){200, 600});
    return weapon;
}

player_t *init_player(window_t *win, p_type_t type)
{
    player_t *player = calloc(1, sizeof(player_t));

    if (!player)
        return NULL;
    player->x = 1.5;
    player->y = 1.5;
    player->z = 1;
    player->angle = fmodf(0.0f, 2.0f * M_PI);
    if (player->angle < 0.0f)
        player->angle += 2.0f * M_PI;
    player->hp = 100;
    player->type = type;
    player->alive = sfTrue;
    player->jump.state = ON_GROUND;
    player->jump.clock = sfClock_create();
    player->weapon = init_weapon(GUN, 34, 9, create_entity("gun",
            "assets/gun.png", &(sfVector2f){win->width / 2, win->height},
            &(sfVector2f){1.7, 1.7}));
    return player;
}
