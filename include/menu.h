/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** Menu, game state and monster functions
*/

#ifndef MENU_H
    #define MENU_H

    #include "types.h"

void menu(wolf_t *wolf);
void manage_menu(wolf_t *wolf, sfEvent event);
void check_player_state(wolf_t *wolf);
void is_near_monster(wolf_t *wolf, player_t *player);

#endif
