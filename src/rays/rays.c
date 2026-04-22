/*
** EPITECH PROJECT, 2026
** rays
** File description:
** rays
*/

#include "../../include/wolf3d.h"
#include <math.h>

static float normalize_angle(float angle)
{
    angle = fmodf(angle, 2.0f * M_PI);
    if (angle < 0.0f)
        angle += 2.0f * M_PI;
    return angle;
}

static void create_pixel(game_t *game, sfUint8 shade,
    sfVector2f *size, window_t *win)
{
    int index = 0;

    if (size->x < 0 || size->x >= win->width ||
        size->y < 0 || size->y >= win->height)
        return;
    index = (size->y * win->width + size->x) * 4;
    game->pixel[index + 0] = shade;
    game->pixel[index + 1] = shade;
    game->pixel[index + 2] = shade;
    game->pixel[index + 3] = 255;
}

static void draw_wall_column(window_t *window_data,
    int column, float distance, game_t *game)
{
    float proj_dist = (window_data->width / 2.0f) / tanf(FOV / 2.0f);
    float wall_height = (TILE_SIZE / distance) * proj_dist;
    float top = (window_data->height - wall_height) / 2.0f;
    int screen_y = 0;
    float attenuation = distance * 0.2f;
    sfUint8 shade = (attenuation >= 255.0f) ? 0 : 255 - attenuation;

    for (int y = 0; y < wall_height; y++) {
        screen_y = top + y;
        if (screen_y >= window_data->height)
            continue;
        create_pixel(game, shade, &(sfVector2f){column, screen_y}, window_data);
    }
}

float cast_single_ray(player_t *player, float ray_angle, window_t *window_data)
{
    float ray_x = player->x;
    float ray_y = player->y;
    float distance = 0.0f;
    float delta_x;
    float delta_y;

    ray_angle = normalize_angle(ray_angle);
    delta_x = cosf(ray_angle) * 0.5f;
    delta_y = sinf(ray_angle) * 0.5f;
    while (!is_wall((int)ray_x, (int)ray_y) &&
        distance < window_data->width * TILE_SIZE) {
        ray_x += delta_x;
        ray_y += delta_y;
        distance += 0.5f;
    }
    return distance * cosf(player->angle - ray_angle);
}

void cast_all_rays(window_t *window_data, player_t *player,
    game_t *game)
{
    float start_angle = player->angle - (FOV / 2.0f);
    float step_angle = FOV / window_data->width;
    float ray_angle;
    float distance;

    memset(game->pixel, 0, window_data->height * window_data->width * 4);
    for (int i = 0; i < window_data->width; i++) {
        ray_angle = normalize_angle(start_angle + (i * step_angle));
        distance = cast_single_ray(player, ray_angle, window_data);
        if (distance < 0.1f)
            distance = 0.1f;
        draw_wall_column(window_data, i, distance, game);
    }
    sfTexture_updateFromPixels(game->texture, game->pixel,
        window_data->width, window_data->height, 0, 0);
    sfRenderWindow_drawSprite(window_data->window, game->sprite, NULL);
}
