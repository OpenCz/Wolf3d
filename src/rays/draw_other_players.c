/*
** EPITECH PROJECT, 2026
** rays
** File description:
** draw other players
*/

#include "../../include/wolf3d.h"
#include <math.h>

static void draw_player_column(game_t *game, window_t *win, int x,
    player_draw_t *draw)
{
    int idx;

    for (int y = draw->top; y < draw->top + draw->height; y++) {
        if (y < 0 || y >= win->height)
            continue;
        idx = (y * win->width + x) * 4;
        game->pixel[idx + 0] = 255;
        game->pixel[idx + 1] = 50;
        game->pixel[idx + 2] = 50;
        game->pixel[idx + 3] = 255;
    }
}

static float wrap_relative_angle(float angle)
{
    while (angle > M_PI)
        angle -= 2.0f * M_PI;
    while (angle < -M_PI)
        angle += 2.0f * M_PI;
    return angle;
}

static void set_player_screen_data(wolf_t *wolf, player_draw_t *draw)
{
    float proj_dist = (wolf->window_data->width / 2.0f) / tanf(FOV / 2.0f);
    float sprite_h = (TILE_SIZE / draw->dist) * proj_dist;

    draw->screen_x = (int)(wolf->window_data->width / 2.0f +
        tanf(draw->rel_angle) * proj_dist);
    draw->height = (int)sprite_h;
    draw->half_w = draw->height / 4;
    draw->top = (wolf->window_data->height - draw->height) / 2;
}

static int fill_player_draw(wolf_t *wolf, player_t *other, player_draw_t *draw)
{
    float dx = other->x - wolf->player->x;
    float dy = other->y - wolf->player->y;

    draw->dist = sqrtf(dx * dx + dy * dy);
    if (draw->dist < 1.0f)
        return -1;
    draw->rel_angle = wrap_relative_angle(
        atan2f(dy, dx) - wolf->player->angle);
    if (fabsf(draw->rel_angle) > FOV / 2.0f + 0.1f)
        return -1;
    set_player_screen_data(wolf, draw);
    return 0;
}

static void draw_projected_player(wolf_t *wolf, player_draw_t *draw)
{
    int width = wolf->window_data->width;

    for (int x = draw->screen_x - draw->half_w; x < draw->screen_x +
        draw->half_w; x++) {
        if ((x < 0 || x >= width) || wolf->game->zbuffer[x] < draw->dist)
            continue;
        draw_player_column(wolf->game, wolf->window_data, x, draw);
    }
}

void draw_other_players(wolf_t *wolf)
{
    player_draw_t draw;

    for (int p = 0; p < wolf->nb_others; p++) {
        if (fill_player_draw(wolf, &wolf->others[p], &draw) < 0)
            continue;
        draw_projected_player(wolf, &draw);
    }
}
