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
        map[map_y][map_x] = 0;
    }
}

static void expand_room(wolf_t *wolf, int map[MAP_HEIGHT][MAP_WIDTH],
    int height, int width)
{
    sfVector2i size = {rand() % 5 + 3, rand() % 5 + 3};
    int random = rand() % 2;
    int list_type = random == 1 ? GARBAGE : MONSTER;
    int type = random == 1 ? GARBAGE_T : ENNEMY;

    if (!is_limit(height, width))
        map[height][width] = 0;
    push_front(&wolf->list[GAME][list_type],
        init_player(wolf->window_data, type,
            &(sfVector2f){width + 0.5, height + 0.5}));
    for (int y = 0; y < size.y; y++)
        expand_room_width(&size, map, &(sfVector2i){height, width}, y);
}

static void create_path_height(int map[MAP_HEIGHT][MAP_WIDTH],
    int x1, int x2, int y)
{
    int start = x1 < x2 ? x1 : x2;
    int end = x1 < x2 ? x2 : x1;

    for (int x = start; x <= end; x++) {
        if (y > 0 && y < MAP_HEIGHT - 1 && x > 0 && x < MAP_WIDTH - 1)
            map[y][x] = 0;
    }
}

static void create_path_width(int map[MAP_HEIGHT][MAP_WIDTH],
    int y1, int y2, int x)
{
    int start = y1 < y2 ? y1 : y2;
    int end = y1 < y2 ? y2 : y1;

    for (int y = start; y <= end; y++) {
        if (y > 0 && y < MAP_HEIGHT - 1 && x > 0 && x < MAP_WIDTH - 1)
            map[y][x] = 0;
    }
}

static void connect_room(int map[MAP_HEIGHT][MAP_WIDTH],
    sfVector2i *pos1, sfVector2i *pos2)
{
    create_path_height(map, pos1->x, pos2->x, pos1->y);
    create_path_width(map, pos1->y, pos2->y, pos2->x);
}

static void set_room(wolf_t *wolf, int map[MAP_HEIGHT][MAP_WIDTH])
{
    int room_count = rand() % 8 + 5;
    int x[room_count];
    int y[room_count];

    set_room_position(room_count, x, MAP_WIDTH, 0);
    set_room_position(room_count, y, MAP_HEIGHT, 1);
    for (int i = 0; i < room_count; i++) {
        expand_room(wolf, map, y[i], x[i]);
        if (i + 1 < room_count)
            connect_room(map, &(sfVector2i){x[i], y[i]},
                &(sfVector2i){x[i + 1], y[i + 1]});
    }
    expand_room(wolf, map, 1, 1);
    connect_room(map, &(sfVector2i){1, 1},
        &(sfVector2i){x[0], y[0]});
}

static void init_map(wall_t *wall)
{
    srand(time(NULL));
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++)
            wall->map[y][x] = 1;
    }
}

void create_map(wolf_t *wolf, wall_t *wall)
{
    init_map(wall);
    set_room(wolf, wall->map);
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++)
            printf("%d ", wall->map[y][x]);
        printf("\n");
    }
}
