/*
** EPITECH PROJECT, 2026
** rays
** File description:
** draw other players
*/

#include "../../include/wolf3d.h"
#include <math.h>

static void add_monster_to_array(wolf_t *wolf, player_t *player, int list_index)
{
    for (list_t *curr = wolf->list[GAME][list_index]; curr; curr = curr->next) {
        player = (player_t *)curr->data;
        if (player->alive != sfTrue)
            continue;
        wolf->game->entities[wolf->game->numSprites] = player;
        wolf->game->numSprites++;
    }
}

static void add_other_player_to_array(wolf_t *wolf)
{
    if (!wolf->connected)
        return;
    for (int i = 0; i < wolf->nb_others; i++) {
        if (wolf->others[i].alive != sfTrue)
            continue;
        wolf->game->entities[wolf->game->numSprites] = &wolf->others[i];
        wolf->game->numSprites++;
    }
}

void add_entity_to_array(wolf_t *wolf)
{
    player_t *player = NULL;

    wolf->game->numSprites = 0;
    add_monster_to_array(wolf, player, MONSTER);
    add_monster_to_array(wolf, player, GARBAGE);
    add_other_player_to_array(wolf);
}
