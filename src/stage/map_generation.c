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
    return (y <= 0 || x <= 0 || y >= MAP_HEIGHT - 1 || x >= MAP_WIDTH - 1);
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
        return;
    }
    for (int i = 0; i < room_count; i++)
        room[i] = rand() % (length - 2) + 1;
}

static void expand_room_width(sfVector2i *size, int map[MAP_HEIGHT][MAP_WIDTH],
    sfVector2i *h, int y)
{
    int map_x = 0;
    int map_y = 0;

    for (int x = 0; x < size->x; x++) {
        map_y = h->x - size->y / 2 + y;
        map_x = h->y - size->x / 2 + x;
        if (is_limit(map_y, map_x))
            continue;
        map[map_y][map_x] = 1;
    }
}

static void expand_room(int map[MAP_HEIGHT][MAP_WIDTH], int height, int width)
{
    sfVector2i size = {rand() % 5 + 3, rand() % 5 + 3};

    map[height][width] = 1;
    for (int y = 0; y < size.y; y++)
        expand_room_width(&size, map, &(sfVector2i){height, width}, y);
}

static void set_room(int map[MAP_HEIGHT][MAP_WIDTH])
{
    int room_count = rand() % 8 + 5;
    int room_x[room_count];
    int room_y[room_count];

    set_room_position(room_count, room_x, MAP_WIDTH, 0);
    set_room_position(room_count, room_y, MAP_HEIGHT, 1);
    for (int i = 0; i < room_count; i++)
        expand_room(map, room_y[i], room_x[i]);
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
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++)
            printf("%d", wall->map[y][x]);
        printf("\n");
    }
}
