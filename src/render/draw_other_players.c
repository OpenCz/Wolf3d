/*
** EPITECH PROJECT, 2026
** rays
** File description:
** draw other players
*/

#include "../../include/wolf3d.h"
#include <math.h>

static void verif_distance(int i, int num, int spriteOrder[],
    double spriteDistance[])
{
    double tmpA;
    int tmpB;

    for (int j = 0; j < num - i - 1; j++) {
        if (spriteDistance[j] < spriteDistance[j + 1]) {
            tmpA = spriteDistance[j];
            spriteDistance[j] = spriteDistance[j + 1];
            spriteDistance[j + 1] = tmpA;
            tmpB = spriteOrder[j];
            spriteOrder[j] = spriteOrder[j + 1];
            spriteOrder[j + 1] = tmpB;
        }
    }
}

static void sort_based_on_dist(int num,
    int spriteOrder[], double spriteDistance[])
{
    for (int i = 0; i < num - 1; i++)
        verif_distance(i, num, spriteOrder, spriteDistance);
}

static void sort_far_to_close(wolf_t *wolf, player_t *p,
    int spriteOrder[], double spriteDistance[])
{
    int num = wolf->game->numSprites;
    player_t **sprite = wolf->game->entities;

    for (int i = 0; i < num; i++) {
        spriteOrder[i] = i;
        spriteDistance[i] = ((p->x - sprite[i]->x) * (p->x - sprite[i]->x) +
            (p->y - sprite[i]->y) * (p->y - sprite[i]->y));
    }
    sort_based_on_dist(num, spriteOrder, spriteDistance);
}

static float get_entity_fog(player_draw_t *d)
{
    float fog = 1.0f - (float)d->distance /
        (FOG_MAX_DIST * (d->type == GARBAGE_T ? 6 : 3));

    return fog < 0.0f ? 0.0f : fog;
}

static void get_index(player_draw_t *draw, sfVector2i *index, sfVector2i *tex)
{
    if (draw->type == GARBAGE_T)
        index->x = (tex->y * TEX_GARBAGE_SHEET_W + tex->x) * 4;
    else
        index->x = (tex->y * TEX_PLAYER_W + tex->x) * 4;
}

static void draw_player_pixel(wolf_t *w, player_draw_t *d,
    int x, sfVector2i *tex)
{
    sfVector2i index;
    game_t *g = w->game;
    int th = d->type == GARBAGE_T ? TEX_GARBAGE_H : TEX_PLAYER_H;
    sfUint8 *pixels = d->type == GARBAGE_T
        ? g->wall->decor_arr[3] : g->wall->decor_arr[2];

    if (d->sprite_height <= 0)
        return;
    for (int y = d->drawStart.y; y < d->drawEnd.y; y++) {
        tex->y = (y - (w->window_data->height / 2 - d->sprite_height / 2) -
            d->offset - (int)w->player->z) * th / d->sprite_height;
        if (tex->y < 0 || tex->y >= th)
            continue;
        get_index(d, &index, tex);
        index.y = (y * w->window_data->width + x) * 4;
        if (index.y >= w->window_data->width * w->window_data->height * 4
            || pixels[index.x + 3] < 128)
            continue;
        create_fog_pixel(g->wall, &index, pixels, get_entity_fog(d));
    }
}

static void draw_entity(wolf_t *wolf, player_draw_t *draw, int spriteScreenX)
{
    sfVector2i tex;
    int tw = draw->type == GARBAGE_T ? TEX_GARBAGE_W : TEX_PLAYER_W;

    if (draw->transform.y <= 0.1 || draw->sprite_width <= 0)
        return;
    for (int x = draw->drawStart.x; x < draw->drawEnd.x; x++) {
        if (draw->transform.y <= 0 || x <= 0 || x >= wolf->window_data->width
            || draw->transform.y >= wolf->game->zbuffer[x])
            continue;
        tex.x = (int)(256 * (x - (-draw->sprite_width / 2 + spriteScreenX))
            * tw / draw->sprite_width) / 256;
        if (tex.x < 0 || tex.x >= tw)
            continue;
        draw_player_pixel(wolf, draw, x, &tex);
    }
}

static void set_sprite_data(wolf_t *wolf,
    player_draw_t *draw, player_t *to_draw, int *spriteScreenX)
{
    sfVector2f dir = {cosf(wolf->player->angle), sinf(wolf->player->angle)};

    draw->type = to_draw->type;
    draw->sprite.x = to_draw->x - wolf->player->x;
    draw->sprite.y = to_draw->y - wolf->player->y;
    get_sprite_height(wolf, draw, &dir, spriteScreenX);
    get_sprite_width(wolf, draw, *spriteScreenX);
}

static void draw_sprite(wolf_t *wolf, player_draw_t *draw,
    int spriteOrder[], double dist[])
{
    player_t **sprite = wolf->game->entities;
    int spriteScreenX = 0;

    draw->plane.x = -sin(wolf->player->angle) * tan(FOV / 2.0f);
    draw->plane.y = cos(wolf->player->angle) * tan(FOV / 2.0f);;
    for (int i = 0; i < draw->num; i++) {
        set_sprite_data(wolf, draw, sprite[spriteOrder[i]], &spriteScreenX);
        draw->distance = dist[i];
        if (wolf->game->has_shot == 1)
            damage_monster(wolf->player->weapon, wolf->window_data,
                draw, sprite[spriteOrder[i]]);
        if (sprite[spriteOrder[i]]->alive == sfFalse)
            continue;
        draw_entity(wolf, draw, spriteScreenX);
    }
    wolf->game->has_shot = 0;
}

void draw_other_entities(wolf_t *wolf, player_t *p)
{
    player_draw_t draw;
    int spriteOrder[MAX_ENTITY];
    double spriteDistance[MAX_ENTITY];

    add_entity_to_array(wolf);
    draw.num = wolf->game->numSprites;
    if (draw.num == 0)
        return;
    sort_far_to_close(wolf, p, spriteOrder, spriteDistance);
    draw_sprite(wolf, &draw, spriteOrder, spriteDistance);
}
