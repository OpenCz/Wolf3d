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
    sfImage *image = NULL;
    const sfUint8 *tmp = NULL;
    int size = TEX_SIZE * TEX_SIZE * 4;

    if (!game)
        return NULL;
    game->clock = sfClock_create();
    game->texture = sfTexture_create(window_data->width, window_data->height);
    game->sprite = sfSprite_create();
    image = sfImage_createFromFile("assets/wall.png");
    tmp = sfImage_getPixelsPtr(image);
    game->wall = malloc(size);
    memcpy(game->wall, tmp, size);
    sfSprite_setTexture(game->sprite, game->texture, sfTrue);
    sfImage_destroy(image);
    return game;
}
