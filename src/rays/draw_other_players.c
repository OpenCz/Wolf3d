/*
** EPITECH PROJECT, 2026
** rays
** File description:
** draw other players
*/

#include "../../include/wolf3d.h"
#include <math.h>

static void sort_far_to_close(wolf_t *wolf, player_t *p,
    int spriteOrder[], double spriteDistance[])
{
    int num = wolf->game->numSprites;
    player_t *sprite = wolf->game->entities;

    for (int i = 0; i < num; i++) {
        spriteOrder[i] = i;
        spriteDistance[i] = ((p->x - sprite[i].x) * (p->x - sprite[i].x) +
            (p->y - sprite[i].y) * (p->y - sprite[i].y));
    }
}

static void get_sprite_height(wolf_t *wolf, player_draw_t *draw,
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
    draw->drawStart.y = -draw->sprite_height / 2 + h / 2;
    if (draw->drawStart.y < 0)
        draw->drawStart.y = 0;
    draw->drawEnd.y = draw->sprite_height / 2 + h / 2;
    if (draw->drawEnd.y >= h)
        draw->drawEnd.y = h - 1;
}

static void get_sprite_width(wolf_t *wolf,
    player_draw_t *draw, int spriteScreenX)
{
    int w = wolf->window_data->width;
    int h = wolf->window_data->height;

    draw->sprite_width = abs((int)(h / (draw->transform.y)));
    draw->drawStart.x = -draw->sprite_width / 2 + spriteScreenX;
    if (draw->drawStart.x < 0)
        draw->drawStart.x = 0;
    draw->drawEnd.x = draw->sprite_width / 2 + spriteScreenX;
    if (draw->drawEnd.x >= w)
        draw->drawEnd.x = w - 1;
}

static void draw_sprite(wolf_t *wolf, player_draw_t *draw,
    int spriteOrder[])
{
    player_t *p = wolf->player;
    player_t *sprite = wolf->game->entities;
    sfVector2f dir = {cosf(p->angle), sinf(p->angle)};
    int spriteScreenX = 0;

    draw->plane.x = -sin(wolf->player->angle) * tan(FOV / 2.0f);
    draw->plane.y = cos(wolf->player->angle) * tan(FOV / 2.0f);;
    for (int i = 0; i < draw->num; i++) {
        draw->sprite.x = sprite[spriteOrder[i]].x - p->x;
        draw->sprite.y = sprite[spriteOrder[i]].y - p->y;
        get_sprite_height(wolf, draw, &dir, &spriteScreenX);
        get_sprite_width(wolf, draw, spriteScreenX);
    }
}

void draw_other_entities(wolf_t *wolf, player_t *p)
{
    player_draw_t draw;
    int spriteOrder[wolf->game->numSprites];
    double spriteDistance[wolf->game->numSprites];

    draw.num = wolf->game->numSprites;
    sort_far_to_close(wolf, p, spriteOrder, spriteDistance);
    draw_sprite(wolf, &draw, spriteOrder);
}
