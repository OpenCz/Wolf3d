/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** Player movement, sprint and collision functions
*/

#ifndef PLAYER_H
    #define PLAYER_H

    #include "types.h"

void sprint_player(player_t *player);
float get_speed(player_t *player, float speed, float accel);
void move_player(player_t *player, sfEvent event, game_t *game);
int check_collision(wall_t *wall, float x, float y);
void open_inventory(wolf_t *wolf, sfEvent event, inv_t *inv);
sfBool iskeypressed(int key, sfEvent event);
void draw_selected_item(window_t *win, inv_t *inv);
void draw_inventory_item(window_t *win, inv_t *inv, int i);
#endif
