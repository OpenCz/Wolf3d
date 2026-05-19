/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** Raycasting and rendering functions
*/

#ifndef RENDER_H
    #define RENDER_H

    #include "types.h"

void cast_all_rays(wolf_t *wolf, window_t *window_data, player_t *player,
    game_t *game);
void render_pixels(game_t *game, window_t *win);
void draw_other_entities(wolf_t *wolf, player_t *p);
float cast_ray(wall_t *wall, player_t *player,
    float ray_dir_x, float ray_dir_y);
void draw_floor_ceiling_rows(wolf_t *w);
void create_pixel(wall_t *wall, int color, int index, sfUint8 *pixel);
void create_fog_pixel(wall_t *wall, sfVector2i *index, sfUint8 *pixel,
    float fog);
void draw_crosshair(wolf_t *wolf, window_t *win);
void draw_sprite_list(wolf_t *wolf);
void draw_text_list(wolf_t *wolf);
void add_entity_to_array(wolf_t *wolf);
void get_sprite_height(wolf_t *wolf, player_draw_t *draw,
    sfVector2f *dir, int *spriteScreenX);
void get_sprite_width(wolf_t *wolf,
    player_draw_t *draw, int spriteScreenX);
#endif
