/*
** EPITECH PROJECT, 2026
** rays
** File description:
** rays
*/

#include "../../include/wolf3d.h"
#include <math.h>

static void update_position(decor_t *d, float dist, wolf_t *w, int col)
{
    float pos_x = w->player->x;
    float pos_y = w->player->y;

    d->floorStep.x = dist * (d->rd1.x - d->rd0.x) / w->window_data->width;
    d->floorStep.y = dist * (d->rd1.y - d->rd0.y) / w->window_data->width;
    d->floor.x = pos_x + dist * d->rd0.x + d->floorStep.x * col;
    d->floor.y = pos_y + dist * d->rd0.y + d->floorStep.y * col;
    d->t.x = (int)(TEX_SIZE * (d->floor.x - (int)d->floor.x)) & (TEX_SIZE - 1);
    d->t.y = (int)(TEX_SIZE * (d->floor.y - (int)d->floor.y)) & (TEX_SIZE - 1);
}

static void draw_floor(wolf_t *w, decor_t *d, int y, int column)
{
    int floor_y = w->window_data->height - 1 - y + 2 * (int)w->player->z;

    if (floor_y < 0 || floor_y >= w->window_data->height)
        return;
    create_pixel(w->game->wall, (TEX_SIZE * d->t.y + d->t.x) * 4,
        (floor_y * w->window_data->width + column) * 4,
        w->game->wall->decor_arr[FLOOR]);
}

static void draw_decor(wolf_t *w, decor_t *d, float wall_height, int column)
{
    int h = w->window_data->height;
    int top = (int)((h - wall_height) / 2.0f + w->player->z);
    int p = 0;

    for (int y = 0; y < top; y++) {
        p = h / 2 - y + (int)w->player->z;
        if (p <= 0)
            continue;
        update_position(d, (0.5f * h) / p * 1.58f, w, column);
        if (y < h)
            create_pixel(w->game->wall, (TEX_SIZE * d->t.y + d->t.x) * 4,
                (y * w->window_data->width + column) * 4,
                w->game->wall->decor_arr[CEILING]);
        draw_floor(w, d, y, column);
    }
}

void draw_ceiling(wolf_t *wolf, int column, float wall_height)
{
    float dir_x = cos(wolf->player->angle);
    float dir_y = sin(wolf->player->angle);
    float plane_len = tan(FOV / 2.0f);
    float plane_x = -sin(wolf->player->angle) * plane_len;
    float plane_y = cos(wolf->player->angle) * plane_len;
    decor_t decor;

    decor.rd0.x = dir_x - plane_x;
    decor.rd0.y = dir_y - plane_y;
    decor.rd1.x = dir_x + plane_x;
    decor.rd1.y = dir_y + plane_y;
    draw_decor(wolf, &decor, wall_height, column);
}
