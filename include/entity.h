/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** Entity, linked list and map utility functions
*/

#ifndef ENTITY_H
    #define ENTITY_H

    #include "types.h"

entity_t *get_entity(list_t *list, char *name);
entity_t *create_entity(char *name,
    const char *texture_path, sfVector2f *pos, sfVector2f *scale);
void push_front(list_t **list, void *data);
int is_wall(wall_t *wall, int x, int y);
extern const int map[MAP_HEIGHT][MAP_WIDTH];
int get_map_tile(int tile_x, int tile_y);

#endif
