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

void check_event(sfRenderWindow *window, sfEvent event)
{
    if (event.type == sfEvtClosed)
        sfRenderWindow_close(window);
}

int main(void)
{
    sfRenderWindow *window;
    sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};
    player_t *player = malloc(sizeof(player_t));
    sfEvent event;

    window = sfRenderWindow_create(mode, "Wolf3D", sfResize | sfClose, NULL);
    if (!window)
        return 1;
    init_player(player);
    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            check_event(window, event);
        }
        sfRenderWindow_clear(window, sfBlack);
        draw_floor_and_ceiling(window);
        // cast_all_rays(window, player);
        sfRenderWindow_display(window);
    }
    sfRenderWindow_destroy(window);
    return 0;
}
