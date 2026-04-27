/*
** EPITECH PROJECT, 2026
** main
** File description:
** main
*/

#include "../../include/wolf3d.h"

void check_player_state(wolf_t *wolf)
{
    if (wolf->player->hp <= 0) {
        wolf->player->hp = 100;
        wolf->state = MENU;
    }
}
