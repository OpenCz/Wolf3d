/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** wolf3d
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#ifndef WOLF_H
    #define WOLF_H

    #define STATES 3
    #define TO_DRAW 2
    #define SPRITE 0
    #define TEXT 1

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

typedef enum {
    MENU,
    GAME,
    SETTINGS,
    QUIT,
} state_t;

typedef struct list_s {
    void *data;
    struct list_s *next;
} list_t;

typedef struct entity_s {
    char *name;
    sfSprite *sprite;
    sfTexture *texture;
} entity_t;

typedef struct wolf_s {
    state_t state;
    player_t *player;
    list_t *list[STATES][TO_DRAW];
} wolf_t;


wolf_t *init_wolf(sfRenderWindow *window);
void init_player(player_t *player);
int is_wall(int x, int y);
void draw_floor_and_ceiling(sfRenderWindow *window);

void draw_sprite_list(wolf_t *wolf, sfRenderWindow *window);
void cast_all_rays(sfRenderWindow *window, player_t *player,
    sfRectangleShape *wall);
float cast_single_ray(player_t *player, float ray_angle,
    sfRenderWindow *window);

void move_player(player_t *player, sfEvent event);
extern const int map[MAP_HEIGHT][MAP_WIDTH];
#endif
