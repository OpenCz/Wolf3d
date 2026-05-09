/*
** EPITECH PROJECT, 2026
** main
** File description:
** main
*/

#include "../../../include/wolf3d.h"

void sprint_player(player_t *player)
{
    if (sfKeyboard_isKeyPressed(sfKeyLShift))
        player->running = sfTrue;
    else
        player->running = sfFalse;
}

float get_speed(player_t *player, float speed, float accel)
{
    if (!sfKeyboard_isKeyPressed(sfKeyS) && player->running) {
        return speed + accel;
    }
    return speed;
}
