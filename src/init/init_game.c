/*
** EPITECH PROJECT, 2026
** init
** File description:
** player
*/

#include "../../include/wolf3d.h"

game_t *init_game(window_t *window_data)
{
    game_t *game = calloc(sizeof(game_t), 1);

    if (!game)
        return NULL;
    game->clock = sfClock_create();
    game->texture = sfTexture_create(window_data->width, window_data->height);
    game->sprite = sfSprite_create();
    sfSprite_setTexture(game->sprite, game->texture, sfTrue);
    return game;
}
