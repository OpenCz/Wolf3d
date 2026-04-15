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

static void draw_wall_column(sfRenderWindow *window, int column, float distance)
{
    sfRectangleShape *wall = sfRectangleShape_create();
    float proj_dist = (WINDOW_WIDTH / 2.0f) / tanf(FOV / 2.0f);
    float wall_height = (TILE_SIZE / distance) * proj_dist;
    float top = (WINDOW_HEIGHT - wall_height) / 2.0f;
    float attenuation = distance * 0.2f;
    sfUint8 shade = (attenuation >= 255.0f) ? 0 : 255 - attenuation;

    if (!wall)
        return;
    sfRectangleShape_setPosition(wall, (sfVector2f){column, top});
    sfRectangleShape_setSize(wall, (sfVector2f){1.0f, wall_height});
    sfRectangleShape_setFillColor(wall, sfColor_fromRGB(shade, shade, shade));
    sfRenderWindow_drawRectangleShape(window, wall, NULL);
    sfRectangleShape_destroy(wall);
}

void cast_all_rays(sfRenderWindow *window, player_t *player)
{
    float start_angle = player->angle - (FOV / 2.0f);
    float step_angle = FOV / NUM_RAYS;
    float ray_angle;
    float distance;

    for (int i = 0; i < NUM_RAYS; i++) {
        ray_angle = normalize_angle(start_angle + (i * step_angle));
        distance = cast_single_ray(player, ray_angle, window);
        if (distance < 0.1f)
            distance = 0.1f;
        draw_wall_column(window, i, distance);
    }
}

float cast_single_ray(player_t *player, float ray_angle, sfRenderWindow *window)
{
    float ray_x = player->x;
    float ray_y = player->y;
    float distance = 0.0f;
    float delta_x;
    float delta_y;

    (void)window;
    ray_angle = normalize_angle(ray_angle);
    delta_x = cosf(ray_angle) * 0.1f;
    delta_y = sinf(ray_angle) * 0.1f;
    while (!is_wall((int)ray_x, (int)ray_y) &&
        distance < MAP_WIDTH * TILE_SIZE) {
        ray_x += delta_x;
        ray_y += delta_y;
        distance += 0.1f;
    }
    return distance * cosf(player->angle - ray_angle);
}
