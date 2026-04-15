/*
** EPITECH PROJECT, 2026
** init
** File description:
** player
*/

#include "../../include/wolf3d.h"
#include <math.h>

void init_player(player_t *player)
{
    if (!player)
        return;
    player->x = TILE_SIZE * 1.5;
    player->y = TILE_SIZE * 1.5;
    player->angle = fmodf(0.0f, 2.0f * M_PI);
    if (player->angle < 0.0f)
        player->angle += 2.0f * M_PI;
}
