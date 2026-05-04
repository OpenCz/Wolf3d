/*
** EPITECH PROJECT, 2026
** init
** File description:
** player
*/

#include "../../include/wolf3d.h"

wall_t *init_texture(wall_t *wall, int size, char *path, sfUint8 **pixel)
{
    sfImage *image = sfImage_createFromFile(path);
    const sfUint8 *tmp = sfImage_getPixelsPtr(image);

    *pixel = malloc(size);
    if (!*pixel)
        return NULL;
    memcpy(*pixel, tmp, size);
    sfImage_destroy(image);
    return wall;
}

wall_t *init_wall(window_t *window_data)
{
    wall_t *wall = malloc(sizeof(wall_t));
    int size = TEX_SIZE * TEX_SIZE * 4;

    if (!wall)
        return NULL;
    wall->wall = malloc(size);
    if (!wall->wall)
        return NULL;
    wall->texture = sfTexture_create(window_data->width, window_data->height);
    wall->sprite = sfSprite_create();
    if (!init_texture(wall, size, "assets/wall.png", &wall->text_arr[0]) ||
        !init_texture(wall, size, "assets/wall_2.png", &wall->text_arr[1]) ||
        !init_texture(wall, size, "assets/ceiling.png", &wall->decor_arr[0]) ||
        !init_texture(wall, size, "assets/floor.png", &wall->decor_arr[1]))
        return NULL;
    sfSprite_setTexture(wall->sprite, wall->texture, sfTrue);
    return wall;
}

game_t *init_game(window_t *window_data)
{
    game_t *game = calloc(sizeof(game_t), 1);

    if (!game)
        return NULL;
    game->clock = sfClock_create();
    game->wall = init_wall(window_data);
    if (!game->wall)
        return NULL;
    return game;
}
