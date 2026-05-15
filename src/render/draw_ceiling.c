/*
** EPITECH PROJECT, 2026
** rays
** File description:
** rays
*/

#include "../../include/wolf3d.h"
#include <math.h>

static void init_decor(decor_t *d, wolf_t *w)
{
    float dir_x = cosf(w->player->angle);
    float dir_y = sinf(w->player->angle);
    float plane_len = tanf(FOV / 2.0f);
    float plane_x = -sinf(w->player->angle) * plane_len;
    float plane_y = cosf(w->player->angle) * plane_len;

    d->rd0.x = dir_x - plane_x;
    d->rd0.y = dir_y - plane_y;
    d->rd1.x = dir_x + plane_x;
    d->rd1.y = dir_y + plane_y;
}

static void init_row(decor_t *d, wolf_t *w, int p, float *dist)
{
    int hw = w->window_data->width;

    *dist = (0.5f * w->window_data->height) / (float)p * 1.58f;
    d->floorStep.x = *dist * (d->rd1.x - d->rd0.x) / hw;
    d->floorStep.y = *dist * (d->rd1.y - d->rd0.y) / hw;
    d->floor.x = w->player->x + *dist * d->rd0.x;
    d->floor.y = w->player->y + *dist * d->rd0.y;
}

static void draw_row(wolf_t *w, decor_t *d, row_t *row)
{
    int hw = w->window_data->width;
    int src = 0;
    int dst = 0;

    for (int x = 0; x < hw; x++) {
        d->t.x = (int)(TEX_SIZE * (d->floor.x - (int)d->floor.x)) &
            (TEX_SIZE - 1);
        d->t.y = (int)(TEX_SIZE * (d->floor.y - (int)d->floor.y)) &
            (TEX_SIZE - 1);
        src = (TEX_SIZE * d->t.y + d->t.x) * 4;
        dst = (row->y * hw + x) * 4;
        create_fog_pixel(w->game->wall, &(sfVector2i){src, dst},
            w->game->wall->decor_arr[row->tex_idx], row->fog);
        d->floor.x += d->floorStep.x;
        d->floor.y += d->floorStep.y;
    }
}

static void fill_row(wolf_t *w, decor_t *d, row_t *row, int p)
{
    float dist = 0;

    init_row(d, w, p, &dist);
    row->fog = 1.0f - dist / FOG_MAX_DIST;
    row->fog = row->fog < 0.0f ? 0.0f : row->fog;
    draw_row(w, d, row);
}

void draw_floor_ceiling_rows(wolf_t *w)
{
    decor_t d;
    row_t row;
    int h = w->window_data->height;
    int horizon = h / 2 + (int)w->player->z;
    int p = 0;

    init_decor(&d, w);
    for (row.y = 0; row.y < h; row.y++) {
        p = (row.y > horizon) ? (row.y - horizon) : (horizon - row.y);
        if (p == 0)
            continue;
        row.tex_idx = (row.y > horizon) ? FLOOR : CEILING;
        fill_row(w, &d, &row, p);
    }
}
