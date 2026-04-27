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

static void create_pixel(wall_t *wall, int color,
    sfVector2f *size, window_t *win)
{
    int index = 0;

    if (size->x < 0 || size->x >= win->width ||
        size->y < 0 || size->y >= win->height)
        return;
    index = ((int)size->y * win->width + (int)size->x) * 4;
    wall->pixel[index + 0] = wall->wall[color];
    wall->pixel[index + 1] = wall->wall[color + 1];
    wall->pixel[index + 2] = wall->wall[color + 2];
    wall->pixel[index + 3] = wall->wall[color + 3];
}

static void draw_wall_column(window_t *win,
    int column, float distance, wall_t *wall)
{
    float proj_dist = (win->width / 2.0f) / tanf(FOV / 2.0f);
    float wall_height = (TILE_SIZE / distance) * proj_dist;
    float top = (win->height - wall_height) / 2.0f;
    int screen_y = 0;
    int text_y = 0;
    int color = 0;

    wall->wall_index = (wall->wall_index < 0) ? 0 : wall->wall_index;
    wall->wall_index = (wall->wall_index > TEX_SIZE - 1) ?
        TEX_SIZE - 1 : wall->wall_index;
    for (int y = 0; y < (int)wall_height; y++) {
        screen_y = (int)top + y;
        if (screen_y < 0 || screen_y >= win->height)
            continue;
        text_y = (int)(((float)y / wall_height) * TEX_SIZE);
        text_y = (text_y < 0) ? 0 : text_y;
        text_y = (text_y > TEX_SIZE - 1) ? TEX_SIZE - 1 : text_y;
        color = (text_y * TEX_SIZE + wall->wall_index) * 4;
        create_pixel(wall, color, &(sfVector2f){column, screen_y}, win);
    }
}

static float cast_ray(wall_t *wall, player_t *player, float ray_angle,
    window_t *window_data)
{
    float ray_x = player->x;
    float ray_y = player->y;
    float delta_x = cosf(ray_angle) * 0.3f;
    float delta_y = sinf(ray_angle) * 0.3f;
    float distance = 0;

    for (; !is_wall(wall, (int)ray_x, (int)ray_y) &&
        distance < window_data->width * TILE_SIZE; distance += 0.3f) {
        ray_x += delta_x;
        ray_y += delta_y;
    }
    return distance;
}

float cast_single_ray(wall_t *wall, player_t *player,
    float ray_angle, window_t *window_data)
{
    float raw = 0;

    ray_angle = normalize_angle(ray_angle);
    raw = cast_ray(wall, player, ray_angle, window_data);
    return raw * cosf(player->angle - ray_angle);
}

static void get_wall_index(player_t *player,
    wall_t *wall, float ray_angle, float distance)
{
    float raw = distance / cosf(player->angle - ray_angle);
    float hx = player->x + cosf(ray_angle) * raw;
    float hy = player->y + sinf(ray_angle) * raw;
    float fx = fmodf(hx, TILE_SIZE);
    float fy = fmodf(hy, TILE_SIZE);
    float wall_frac = (fminf(fx, TILE_SIZE - fx) < fminf(fy, TILE_SIZE - fy))
        ? fy / TILE_SIZE : fx / TILE_SIZE;

    wall->wall_index = (int)(wall_frac * TEX_SIZE);
    if (wall->wall_index < 0)
        wall->wall_index = 0;
    if (wall->wall_index > TEX_SIZE - 1)
        wall->wall_index = TEX_SIZE - 1;
}

void cast_all_rays(window_t *window_data, player_t *player,
    game_t *game)
{
    float start_angle = player->angle - (FOV / 2.0f);
    float step_angle = FOV / window_data->width;
    float ray_angle = 0;
    float distance = 0;

    memset(game->wall->pixel, 0, window_data->height * window_data->width * 4);
    for (int i = 0; i < window_data->width; i++) {
        ray_angle = normalize_angle(start_angle + (i * step_angle));
        distance = cast_single_ray(game->wall, player, ray_angle, window_data);
        if (distance < 10.f)
            distance = 10.f;
        get_wall_index(player, game->wall, ray_angle, distance);
        draw_wall_column(window_data, i, distance, game->wall);
        game->zbuffer[i] = distance;
    }
}

void render_pixels(game_t *game, window_t *win)
{
    sfTexture_updateFromPixels(game->wall->texture, game->wall->pixel,
        win->width, win->height, 0, 0);
    sfRenderWindow_drawSprite(win->window, game->wall->sprite, NULL);
}
