/*
** EPITECH PROJECT, 2026
** rays
** File description:
** draw other players
*/

#include "../../include/wolf3d.h"
#include <math.h>

void get_sprite_height(wolf_t *wolf, player_draw_t *draw,
    sfVector2f *dir, int *spriteScreenX)
{
    double i = 0;
    int h = wolf->window_data->height;
    int w = wolf->window_data->width;

    i = 1.0 / (draw->plane.x * dir->y - dir->x * draw->plane.y);
    draw->transform.x = i * (dir->y * draw->sprite.x - dir->x * draw->sprite.y);
    draw->transform.y = i * (-draw->plane.y * draw->sprite.x +
        draw->plane.x * draw->sprite.y);
    *spriteScreenX = (int)((w / 2) * (1 + draw->transform.x /
            draw->transform.y));
    draw->sprite_height = abs((int)(h / (draw->transform.y)));
    draw->offset = draw->sprite_height / (draw->type == GARBAGE_T ? 2 : 4);
    draw->drawStart.y = -draw->sprite_height / 2 + h / 2 + draw->offset +
        (int)wolf->player->z;
    if (draw->drawStart.y < 0)
        draw->drawStart.y = 0;
    draw->drawEnd.y = draw->sprite_height / 2 + h / 2 + draw->offset +
        (int)wolf->player->z;
    if (draw->drawEnd.y >= h)
        draw->drawEnd.y = h - 1;
}

void get_sprite_width(wolf_t *wolf,
    player_draw_t *draw, int spriteScreenX)
{
    int w = wolf->window_data->width;
    int h = wolf->window_data->height;
    int tw = draw->type == GARBAGE_T ? TEX_GARBAGE_W : TEX_PLAYER_W;
    int th = draw->type == GARBAGE_T ? TEX_GARBAGE_H : TEX_PLAYER_H;

    draw->sprite_width = abs((int)(h / draw->transform.y * tw / th));
    draw->drawStart.x = -draw->sprite_width / 2 + spriteScreenX;
    if (draw->drawStart.x < 0)
        draw->drawStart.x = 0;
    draw->drawEnd.x = draw->sprite_width / 2 + spriteScreenX;
    if (draw->drawEnd.x >= w)
        draw->drawEnd.x = w - 1;
}
