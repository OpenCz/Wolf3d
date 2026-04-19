/*
** EPITECH PROJECT, 2026
** init
** File description:
** player
*/

#include "../../include/wolf3d.h"

game_t *init_game(void)
{
    game_t *game = calloc(sizeof(game_t), 1);

    if (!game)
        return NULL;
    game->clock = sfClock_create();
    game->wall = sfRectangleShape_create();
    return game;
}
