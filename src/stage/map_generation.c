/*
** EPITECH PROJECT, 2026
** stage
** File description:
** stage
*/

#include "../include/wolf3d.h"
#include <time.h>

static int is_limit(int y, int x)
{
    return (y == 0 || x == 0 || y == MAP_HEIGHT || x == MAP_WIDTH);
}

static void set_room_position(int room_count, int room[room_count],
    int length, int mod)
{
    int min = 0;
    int max = 0;
    int dist = length / room_count;

    if (mod == 0) {
        for (int i = 0; i < room_count; i++) {
            min = i * dist;
            max = min + dist - 1;
            room[i] = min + rand() % (max - min + 1);
        }
    } else {
        for (int i = 0; i < room_count; i++) {
            room[i] = rand() % (length - 1);
            room[i] = room[i] == 0 ? room[i] == 1 : room[i];
        }
    }
}

static void expand_room(int map[MAP_HEIGHT][MAP_WIDTH], int y, int x)
{
    map[y][x] = 0;
}

static void set_room(int map[MAP_HEIGHT][MAP_WIDTH])
{
    int room_count = rand() % 2 + 5;
    int room_x[room_count];
    int room_y[room_count];

    set_room_position(room_count, room_x, MAP_WIDTH, 0);
    set_room_position(room_count, room_y, MAP_HEIGHT, 1);
    for (int i = 0; i < room_count; i++)
        map[room_y[i]][room_x[i]] = 1;
}

static void init_map(wall_t *wall)
{
    srand(time(NULL));
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++)
            wall->map[y][x] = 0;
    }
}

void create_map(wall_t *wall)
{
    init_map(wall);
    set_room(wall->map);
}
