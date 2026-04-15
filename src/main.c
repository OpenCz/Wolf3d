/*
** EPITECH PROJECT, 2026
** main
** File description:
** main
*/

#include "../include/wolf3d.h"

const int map[MAP_HEIGHT][MAP_WIDTH] = {
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
    if (event.type == sfEvtClosed || wolf->state == QUIT ||
        sfKeyboard_isKeyPressed(sfKeyEscape))
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

int program(sfRenderWindow *window, sfEvent event, wolf_t *wolf)
{
    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event))
            check_event(window, event, wolf);
        check_state(wolf, window, event);
        draw_sprite_list(wolf, window);
        sfRenderWindow_display(window);
    }
    sfRenderWindow_destroy(window);
    return 0;
}

int main(void)
{
    sfRenderWindow *window = sfRenderWindow_create((sfVideoMode)
        {1920, 1080, 32}, "Wolf3D", sfResize, NULL);
    wolf_t *wolf = init_wolf(window);
    sfEvent event;

    if (!wolf)
        return 84;
    return program(window, event, wolf);
}
