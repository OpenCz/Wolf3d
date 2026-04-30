/*
** EPITECH PROJECT, 2026
** rays
** File description:
** rays
*/

#include "../../include/wolf3d.h"
#include <math.h>

static void draw_decor(wolf_t *w, sfVector2f *raydir0, sfVector2f *raydir1, float wall_height, int column)
{
    sfVector2i t;
    sfVector2f floor;
    sfVector2f floorStep;
    float rowDistance = 0;
    int p;
    int index = 0;
    int top = (int)((w->window_data->height - wall_height) / 2.0f);

    for (int y = 0; y < top; y++) {
        p = w->window_data->height / 2 - y;
        if (p <= 0)
            continue;
        rowDistance = (0.5f * w->window_data->height) / p;
        floorStep.x = rowDistance * (raydir1->x - raydir0->x) / w->window_data->width;
        floorStep.y = rowDistance * (raydir1->y - raydir0->y) / w->window_data->width;
        floor.x = w->player->x + rowDistance * raydir0->x + floorStep.x * column;
        floor.y = w->player->y + rowDistance * raydir0->y + floorStep.y * column;
        t.x = (int)(TEX_SIZE * (floor.x - (int)floor.x)) & (TEX_SIZE - 1);
        t.y = (int)(TEX_SIZE * (floor.y - (int)floor.y)) & (TEX_SIZE - 1);
        index = (y * w->window_data->width + column) * 4;
        create_pixel(w->game->wall, (TEX_SIZE * t.y + t.x) * 4, index, w->game->wall->decor_arr[CEILING]);
    }
}

void draw_ceiling(wolf_t *wolf, int column, float wall_height)
{
    float dir_x = cos(wolf->player->angle);
    float dir_y = sin(wolf->player->angle);
    float plane_len = tan(FOV / 2.0f);
    float plane_x = -sin(wolf->player->angle) * plane_len;
    float plane_y = cos(wolf->player->angle) * plane_len;
    float rayDirX0 = dir_x - plane_x;
    float rayDirY0 = dir_y - plane_y;
    float rayDirX1 = dir_x + plane_x;
    float rayDirY1 = dir_y + plane_y;

    draw_decor(wolf, &(sfVector2f){rayDirX0, rayDirY0}, &(sfVector2f){rayDirX1, rayDirY1}, wall_height, column);
}
