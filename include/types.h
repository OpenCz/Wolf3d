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
    int attack_speed;
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

typedef enum {
    GRAPHICS,
    AUDIO,
    GAMEPLAY,
    CONTROLS,
    ACCESSIBILITY,
} settings_t;

typedef struct settings_game_s {
    sfVideoMode resolution;
    sfBool fullscreen;
    sfBool vsync;
    int fov;
    int brightness;
    int max_fps;
    int master_volume;
    int music_volume;
    int sfx_volume;
    int ambient_volume;
    int mouse_sensitivity;
    sfBool invert_mouse;
    sfBool show_hud;
    sfBool show_fps;
    sfBool show_minimap;
    sfBool crosshair;
} settings_game_t;

typedef enum {
    TYPE_MENU,
    TYPE_SETTINGS
} type_t;

typedef struct triangle_s triangle_t;

typedef struct vertex_s {
    sfVector2f start;
    sfVector2f end;
    sfVertex vertex;
} vertex_t;

typedef struct rect_s {
    char *name;
    int state;
    sfRectangleShape *rect;
    sfTexture *texture;
    sfTexture *click_texture;
    type_t type;
    sfBool always_display;
} rect_t;

typedef struct text_s {
    char *name;
    char *content;
    int state;
    type_t type;
    sfText *text;
    sfBool always_display;
    triangle_t *left_triangle;
    triangle_t *right_triangle;
} text_t;

struct triangle_s {
    sfConvexShape *shape;
    char *name;
    int state;
    int type;
};

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
    settings_game_t *settings;
    settings_game_t *tmp_settings;
    state_t state;
    int menu_state;
    int settings_state;
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
