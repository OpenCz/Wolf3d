/*
** EPITECH PROJECT, 2026
** main
** File description:
** main
*/

#include "../include/wolf3d.h"

int get_map_tile(int tile_x, int tile_y)
{
    static const int map_data[MAP_HEIGHT][MAP_WIDTH] = {
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1}
    };

    return map_data[tile_y][tile_x];
}

void check_event(sfRenderWindow *window, sfEvent event, wolf_t *wolf)
{
    if (event.type == sfEvtClosed || wolf->state == QUIT ||
        sfKeyboard_isKeyPressed(sfKeyEscape))
        sfRenderWindow_close(window);
    if (sfKeyboard_isKeyPressed(sfKeyEnter))
        wolf->state = GAME;
}

static void stage(wolf_t *wolf, player_t *player, sfEvent event)
{
    sfRectangleShape *wall = sfRectangleShape_create();

    move_player(player, event);
    sfRenderWindow_clear(wolf->window_data->window, sfBlack);
    draw_floor_and_ceiling(wolf->window_data);
    cast_all_rays(wolf->window_data, player, wall);
    sfRectangleShape_destroy(wall);
}

static void check_state(wolf_t *wolf, sfEvent event)
{
    switch (wolf->state) {
        case MENU:
            break;
        case GAME:
            stage(wolf, wolf->player, event);
            break;
        default:
            break;
    }
}

int program(sfRenderWindow *window, sfEvent event, wolf_t *wolf)
{
    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event))
            check_event(window, event, wolf);
        check_state(wolf, event);
        draw_sprite_list(wolf, window);
        sfRenderWindow_display(window);
    }
    sfRenderWindow_destroy(window);
    return 0;
}

int main(void)
{
    wolf_t *wolf = init_wolf();
    sfEvent event;

    if (!wolf)
        return 84;
    return program(wolf->window_data->window, event, wolf);
}
