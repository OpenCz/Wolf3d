/*
** EPITECH PROJECT, 2026
** main
** File description:
** main
*/

#include "../include/wolf3d.h"

int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}
};

void check_event(sfRenderWindow *window, sfEvent event, wolf_t *wolf)
{
    if (event.type == sfEvtClosed || wolf->state == QUIT)
        sfRenderWindow_close(window);
}

static void stage(sfRenderWindow *window, player_t *player, sfEvent event)
{
    sfRectangleShape *wall = sfRectangleShape_create();

    move_player(player, event);
    sfRenderWindow_clear(window, sfBlack);
    draw_floor_and_ceiling(window);
    cast_all_rays(window, player, wall);
    sfRectangleShape_destroy(wall);
}

static void check_state(wolf_t *wolf, sfRenderWindow *window, sfEvent event)
{
    switch (wolf->state) {
        case MENU:
            break;
        case GAME:
            stage(window, wolf->player, event);
            break;
        default:
            break;
    }
}

int main(void)
{
    sfRenderWindow *window;
    sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};
    wolf_t *wolf = calloc(1, sizeof(wolf_t));
    sfEvent event;

    window = sfRenderWindow_create(mode, "Wolf3D", sfResize | sfClose, NULL);
    if (!window)
        return 1;
    init_player(wolf->player);
    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event))
            check_event(window, event, wolf);
        check_state(wolf, window, event);
        sfRenderWindow_display(window);
    }
    sfRenderWindow_destroy(window);
    return 0;
}
