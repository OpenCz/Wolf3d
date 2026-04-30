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
    d->floorStep.x = dist * (d->rd1.x - d->rd0.x) / w->window_data->width;
    d->floorStep.y = dist * (d->rd1.y - d->rd0.y) / w->window_data->width;
    d->floor.x = w->player->x + dist * d->rd0.x + d->floorStep.x * col;
    d->floor.y = w->player->y + dist * d->rd0.y + d->floorStep.y * col;
    d->t.x = (int)(TEX_SIZE * (d->floor.x - (int)d->floor.x)) &
        (TEX_SIZE - 1);
    d->t.y = (int)(TEX_SIZE * (d->floor.y - (int)d->floor.y)) &
        (TEX_SIZE - 1);
}

static void draw_decor(wolf_t *w, decor_t *d, float wall_height, int column)
{
    float dist = 0;
    int p;
    int index = 0;
    int top = (int)((w->window_data->height - wall_height) / 2.0f);
    int color = 0;

    for (int y = 0; y < top; y++) {
        p = w->window_data->height / 2 - y;
        if (p <= 0)
            continue;
        dist = (0.5f * w->window_data->height) / p;
        update_position(d, dist, w, column);
        index = (y * w->window_data->width + column) * 4;
        color = (TEX_SIZE * d->t.y + d->t.x) * 4;
        create_pixel(w->game->wall, color, index,
            w->game->wall->decor_arr[CEILING]);
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
