/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** wolf3d
*/

#include <SFML/Graphics.h>
#include <stdlib.h>

#ifndef WOLF_H
    #define WOLF_H

    #define M_PI 3.1415

    #define TILE_SIZE 64
    #define MAP_WIDTH 8
    #define MAP_HEIGHT 8
    #define WINDOW_WIDTH 800
    #define WINDOW_HEIGHT 600

    #define FOV (M_PI / 3)
    #define NUM_RAYS 800

typedef struct player_s {
    float x;
    float y;
    float angle;
} player_t;

void init_player(player_t *player);
int is_wall(int x, int y);
void draw_floor_and_ceiling(sfRenderWindow *window);

void cast_all_rays(sfRenderWindow *window, player_t *player);
float cast_single_ray(player_t *player, float ray_angle,
    sfRenderWindow *window);

extern int map[MAP_HEIGHT][MAP_WIDTH];
#endif
