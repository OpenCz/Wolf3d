/*
** EPITECH PROJECT, 2026
** main
** File description:
** main
*/

#include "../../../include/wolf3d.h"

void move_player(player_t *player, sfEvent event)
{
    if (sfKeyboard_isKeyPressed(sfKeyZ)) {
        player->x += cosf(player->angle) * 0.3;
        player->y += sinf(player->angle) * 0.3;
    }
    if (sfKeyboard_isKeyPressed(sfKeyS)) {
        player->x -= cosf(player->angle) * 0.3;
        player->y -= sinf(player->angle) * 0.3;
    }
    if (sfKeyboard_isKeyPressed(sfKeyQ)) {
        player->x += cosf(player->angle - M_PI / 2) * 0.3;
        player->y += sinf(player->angle - M_PI / 2) * 0.3;
    }
    if (sfKeyboard_isKeyPressed(sfKeyD)) {
        player->x += cosf(player->angle + M_PI / 2) * 0.3;
        player->y += sinf(player->angle + M_PI / 2) * 0.3;
    }
    if (sfKeyboard_isKeyPressed(sfKeyRight))
        player->angle += 0.009;
    if (sfKeyboard_isKeyPressed(sfKeyLeft))
        player->angle -= 0.009;
}
