/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** Initialization and cleanup functions
*/

#ifndef INIT_H
    #define INIT_H

    #include "types.h"

wolf_t *init_wolf(void);
void init_menu_text(wolf_t *wolf, window_t *window);
game_t *init_game(window_t *window_data);
player_t *init_player(window_t *win, p_type_t type);
void init_menu_entities(wolf_t *wolf, window_t *window);
void free_wolf(wolf_t *wolf);
window_t *create_inv(data_t *data, window_t *win, inv_t *inv);
weapon_t *init_weapon(wp_type_t type, int damage,
    int max_ammo, entity_t *entity);

#endif
