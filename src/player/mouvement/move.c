/*
** EPITECH PROJECT, 2026
** main
** File description:
** main
*/

#include "../../../include/wolf3d.h"

static void manage_angle(player_t *player, float dt)
{
    float rotation_speed = 2.0f;

    if (sfKeyboard_isKeyPressed(sfKeyRight))
        player->angle += rotation_speed * dt;
    if (sfKeyboard_isKeyPressed(sfKeyLeft))
        player->angle -= rotation_speed * dt;
}

void move_player(player_t *player, sfEvent event, game_t *game)
{
    float dt = sfTime_asSeconds(sfClock_getElapsedTime(game->clock));

    sfClock_restart(game->clock);
    if (sfKeyboard_isKeyPressed(sfKeyZ)) {
        player->x += cosf(player->angle) * 100 * dt;
        player->y += sinf(player->angle) * 100 * dt;
    }
    if (sfKeyboard_isKeyPressed(sfKeyS)) {
        player->x -= cosf(player->angle) * 100 * dt;
        player->y -= sinf(player->angle) * 100 * dt;
    }
    if (sfKeyboard_isKeyPressed(sfKeyQ)) {
        player->x += cosf(player->angle - M_PI / 2) * 100 * dt;
        player->y += sinf(player->angle - M_PI / 2) * 100 * dt;
    }
    if (sfKeyboard_isKeyPressed(sfKeyD)) {
        player->x += cosf(player->angle + M_PI / 2) * 100 * dt;
        player->y += sinf(player->angle + M_PI / 2) * 100 * dt;
    }
    manage_angle(player, dt);
}
