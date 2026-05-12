/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** Utility functions
*/

#ifndef UTILS_H
    #define UTILS_H

    #include "types.h"

char *my_nbr_to_str(int nb);
sfBool iskeypressed(int key, sfEvent event);
void draw_other_players(wolf_t *wolf);

#endif
