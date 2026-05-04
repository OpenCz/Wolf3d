/*
** EPITECH PROJECT, 2026
** rays
** File description:
** rays
*/

#include "../../include/wolf3d.h"
#include <math.h>

void draw_wall(wall_t *wall, float wall_height, window_t *win, int column)
{
    float top = (win->height - wall_height) / 2.0f;
    int screen_y = 0;
    int text_y = 0;
    int color = 0;
    int index = 0;

    for (int y = 0; y < (int)wall_height; y++) {
        screen_y = (int)top + y;
        if (screen_y < 0 || screen_y >= win->height)
            continue;
        text_y = (int)(((float)y / wall_height) * TEX_SIZE);
        text_y = (text_y < 0) ? 0 : text_y;
        text_y = (text_y > TEX_SIZE - 1) ? TEX_SIZE - 1 : text_y;
        color = (text_y * TEX_SIZE + wall->wall_index) * 4;
        index = ((int)screen_y * win->width + (int)column) * 4;
        if (!(index < 0 || index >= win->width * win->height * 4))
            create_pixel(wall, color, index, wall->wall);
    }
}

static void draw_wall_column(wolf_t *wolf,
    int column, float distance, wall_t *wall)
{
    float proj_dist = (wolf->window_data->width / 2.0f) / tanf(FOV / 2.0f);
    float wall_height = (1.0f / distance) * proj_dist;

    wall->wall_index = (wall->wall_index < 0) ? 0 : wall->wall_index;
    wall->wall_index = (wall->wall_index > TEX_SIZE - 1) ?
        TEX_SIZE - 1 : wall->wall_index;
    draw_wall(wall, wall_height, wolf->window_data, column);
    draw_ceiling(wolf, column, wall_height);
}

static void get_wall_index(wall_t *wall, player_t *player,
    sfVector2f *ray_dir, float distance)
{
    float hx = player->x + ray_dir->x * distance;
    float hy = player->y + ray_dir->y * distance;
    float fx = fmodf(hx, 1.0f);
    float fy = fmodf(hy, 1.0f);
    float wall_frac = (fminf(fx, 1.0f - fx) < fminf(fy, 1.0f - fy))
        ? fy : fx;

    wall->wall_index = (int)(wall_frac * TEX_SIZE);
    if (wall->wall_index < 0)
        wall->wall_index = 0;
    if (wall->wall_index > TEX_SIZE - 1)
        wall->wall_index = TEX_SIZE - 1;
}

void cast_all_rays(wolf_t *wolf, window_t *window_data, player_t *player,
    game_t *game)
{
    sfVector2f dir = {cosf(player->angle), sinf(player->angle)};
    float plane_len = tanf(FOV / 2.0f);
    float pl_x = -sinf(player->angle) * plane_len;
    float pl_y = cosf(player->angle) * plane_len;
    float camera_x = 0;
    float distance = 0;
    sfVector2f raydir = {dir.x + pl_x * camera_x, dir.y + pl_y * camera_x};

    memset(game->wall->pixel, 0, window_data->height * window_data->width * 4);
    for (int i = 0; i < window_data->width; i++) {
        camera_x = 2.0f * i / window_data->width - 1.0f;
        raydir.x = dir.x + pl_x * camera_x;
        raydir.y = dir.y + pl_y * camera_x;
        distance = cast_ray(game->wall, player, raydir.x, raydir.y);
        if (distance < 0.1f)
            distance = 0.1f;
        get_wall_index(game->wall, player, &raydir, distance);
        draw_wall_column(wolf, i, distance, game->wall);
        game->zbuffer[i] = distance;
    }
}

void render_pixels(game_t *game, window_t *win)
{
    sfTexture_updateFromPixels(game->wall->texture, game->wall->pixel,
        win->width, win->height, 0, 0);
    sfRenderWindow_drawSprite(win->window, game->wall->sprite, NULL);
}
