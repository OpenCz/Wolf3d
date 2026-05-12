/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** Weapon and animation functions
*/

#ifndef WEAPON_H
    #define WEAPON_H

    #include "types.h"

void draw_weapon(wolf_t *wolf, window_t *win, weapon_t *weapon);
void use_weapon(game_t *game, weapon_t *weapon);
void animate_weapon_walk(wolf_t *wolf, window_t *win, weapon_t *weapon);
void damage_monster(weapon_t *weapon, window_t *win,
    player_draw_t *draw, player_t *monster);

#endif
