/*
** EPITECH PROJECT, 2026
** init
** File description:
** player
*/

#include "../../include/wolf3d.h"
#include <math.h>

player_t *init_player(void)
{
    player_t *player = calloc(1, sizeof(player_t));

    if (!player)
        return NULL;
    player->x = TILE_SIZE * 1.5;
    player->y = TILE_SIZE * 1.5;
    player->angle = fmodf(0.0f, 2.0f * M_PI);
    if (player->angle < 0.0f)
        player->angle += 2.0f * M_PI;
    player->hp = 100;
    return player;
}
