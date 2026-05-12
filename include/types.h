/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** All game types, structs and enums
*/

#ifndef TYPES_H
    #define TYPES_H

    #include <SFML/Graphics.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include "constants.h"
    #include "network.h"

typedef struct entity_s {
    char *name;
    sfClock *clock;
    sfSprite *sprite;
    sfTexture *texture;
} entity_t;

typedef enum {
    PLAYER,
    ENNEMY,
} p_type_t;

typedef enum {
    GUN,
} wp_type_t;

typedef struct weapon_s {
    sfClock *cd;
    wp_type_t type;
    sfIntRect rect;
    int max_ammo;
    int current_ammo;
    int damage;
    float attack_speed;
    int current_frame;
    int reloading;
    entity_t *entity;
} weapon_t;

typedef struct player_s {
    float x;
    float y;
    float angle;
    int hp;
    p_type_t type;
    weapon_t *weapon;
    sfBool alive;
    sfBool running;
} player_t;

typedef enum {
    MENU,
    GAME,
    SETTINGS,
    QUIT,
} state_t;

typedef enum {
    NEWGAME,
    CONTINUE,
    OPTIONS,
    LEAVE,
} menu_t;

typedef struct player_draw_s {
    int num;
    sfVector2f sprite;
    sfVector2f plane;
    sfVector2f transform;
    int sprite_height;
    int sprite_width;
    sfVector2f drawStart;
    sfVector2f drawEnd;
    int offset;
} player_draw_t;

typedef struct list_s {
    void *data;
    struct list_s *next;
} list_t;

typedef struct text_s {
    char *name;
    char *content;
    menu_t state;
    sfText *text;
} text_t;

typedef struct wall_s {
    sfUint8 *wall;
    int wall_index;
    sfTexture *texture;
    sfSprite *sprite;
    sfUint8 *pixel;
    sfUint8 *text_arr[2];
    sfUint8 *decor_arr[3];
} wall_t;

typedef struct crosshair_s {
    sfVector2f pos;
    entity_t *cursor;
} crosshair_t;

typedef struct game_s {
    sfClock *clock[2];
    player_t *entities[MAX_ENTITY];
    int numSprites;
    wall_t *wall;
    float *zbuffer;
    int has_shot;
    crosshair_t crosshair;
} game_t;

typedef struct window_s {
    sfRenderWindow *window;
    int width;
    int height;
} window_t;

typedef struct data_s {
    sfFont *font;
} data_t;

typedef struct decor_s {
    sfVector2i t;
    sfVector2f floor;
    sfVector2f floorStep;
    sfVector2f rd0;
    sfVector2f rd1;
} decor_t;

typedef struct ray_s {
    sfVector2i map;
    sfVector2f delta_dist;
    sfVector2f side_dist;
    sfVector2i step;
} ray_t;

typedef struct wolf_s {
    state_t state;
    menu_t menu_state;
    player_t *player;
    window_t *window_data;
    data_t *data;
    game_t *game;
    list_t *list[STATES][TO_DRAW];
    client_t net;
    int connected;
    player_t others[MAX_PLAYERS];
    int nb_others;
} wolf_t;

#endif
