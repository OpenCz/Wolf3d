/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** Stage and stage functions
*/

#ifndef STAGE_H
    #define STAGE_H

    #include "types.h"
void create_map(wolf_t *wolf, wall_t *wall);
void stage(wolf_t *wolf, player_t *player, sfEvent event);
#endif
