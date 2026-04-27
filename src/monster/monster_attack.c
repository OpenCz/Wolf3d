/*
** EPITECH PROJECT, 2026
** main
** File description:
** main
*/

#include "../../include/wolf3d.h"

int is_in_range(player_t *player, player_t *monster)
{
    return player->x > monster->x - 30 && player->x < monster->x + 30 &&
        player->y > monster->y - 30 && player->y < monster->y + 30;
}

void is_near_monster(wolf_t *wolf, player_t *player)
{
    player_t *monster;

    for (list_t *curr = wolf->list[GAME][MONSTER]; curr; curr = curr->next) {
        monster = (player_t *)curr->data;
        if (is_in_range(player, monster)) {
            player->hp -= 1;
        }
    }
}
