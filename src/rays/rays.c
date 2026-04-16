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

static void draw_wall_column(window_t *window_data,
    int column, float distance, sfRectangleShape *wall)
{
    float proj_dist = (window_data->width / 2.0f) / tanf(FOV / 2.0f);
    float wall_height = (TILE_SIZE / distance) * proj_dist;
    float top = (window_data->height - wall_height) / 2.0f;
    float attenuation = distance * 0.2f;
    sfUint8 shade = (attenuation >= 255.0f) ? 0 : 255 - attenuation;

    sfRectangleShape_setPosition(wall, (sfVector2f){column, top});
    sfRectangleShape_setSize(wall, (sfVector2f){1.0f, wall_height});
    sfRectangleShape_setFillColor(wall, sfColor_fromRGB(shade, shade, shade));
    sfRenderWindow_drawRectangleShape(window_data->window, wall, NULL);
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
    sfRectangleShape *wall)
{
    float start_angle = player->angle - (FOV / 2.0f);
    float step_angle = FOV / window_data->width;
    float ray_angle;
    float distance;

    for (int i = 0; i < window_data->width; i++) {
        ray_angle = normalize_angle(start_angle + (i * step_angle));
        distance = cast_single_ray(player, ray_angle, window_data);
        if (distance < 0.1f)
            distance = 0.1f;
        draw_wall_column(window_data, i, distance, wall);
    }
}
