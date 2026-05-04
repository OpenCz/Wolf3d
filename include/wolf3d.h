/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** wolf3d
*/


#ifndef WOLF_H
    #include <math.h>
    #define WOLF_H
    #define WALL_MIN_DISTANCE TILE_SIZE * 0.15
    #define STATES 3
    #define TO_DRAW 3
    #define SPRITE 0
    #define TEXT 1
    #define MONSTER 2
    #define NUM_RAYS 800
    #define TILE_SIZE 64
    #define MAP_WIDTH 8
    #define MAP_HEIGHT 8
    #define WINDOW_WIDTH 800
    #define WINDOW_HEIGHT 600
    #define FOV (M_PI / 3)
    #define TEX_SIZE 64
    #define CLOUD_SPEED 20
    #include <SFML/Graphics.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include "network.h"

typedef struct player_s {
    float x;
    float y;
    float angle;
    int hp;
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
    float dist;
    float rel_angle;
    int screen_x;
    int half_w;
    int top;
    int height;
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

typedef struct entity_s {
    char *name;
    sfClock *clock;
    sfSprite *sprite;
    sfTexture *texture;
} entity_t;

typedef struct wall_s {
    sfUint8 *wall;
    int wall_index;
    sfTexture *texture;
    sfSprite *sprite;
    sfUint8 *pixel;
    sfUint8 *text_arr[2];
} wall_t;

typedef struct game_s {
    sfClock *clock;
    wall_t *wall;
    float *zbuffer;
} game_t;

typedef struct window_s {
    sfRenderWindow *window;
    int width;
    int height;
} window_t;

typedef struct data_s {
    sfFont *font;
} data_t;

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

void is_near_monster(wolf_t *wolf, player_t *player);
void menu(wolf_t *wolf);
wolf_t *init_wolf(void);
void init_menu_text(wolf_t *wolf, window_t *window);
game_t *init_game(window_t *window_data);
player_t *init_player(void);
void init_menu_entities(wolf_t *wolf, window_t *window);
entity_t *get_entity(list_t *list, char *name);
void free_wolf(wolf_t *wolf);
int is_wall(wall_t *wall, int x, int y);
void draw_floor_and_ceiling(window_t *window_data);

void check_player_state(wolf_t *wolf);
void draw_sprite_list(wolf_t *wolf);
void draw_text_list(wolf_t *wolf);
void cast_all_rays(window_t *window_data, player_t *player, game_t *game);
void render_pixels(game_t *game, window_t *win);
void draw_other_players(wolf_t *wolf);

void free_wolf(wolf_t *wolf);
void move_player(player_t *player, sfEvent event, game_t *game);
extern const int map[MAP_HEIGHT][MAP_WIDTH];
int get_map_tile(int tile_x, int tile_y);
void push_front(list_t **list, void *data);
void manage_menu(wolf_t *wolf, sfEvent event);
void settings(wolf_t *wolf);
void manage_settings(wolf_t *wolf, sfEvent event);
#endif
