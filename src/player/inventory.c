/*
** EPITECH PROJECT, 2026
** weapon
** File description:
** weapon
*/

#include "../../include/wolf3d.h"

static void manage_inventory(window_t *win, inv_t *inv)
{
    sfVector2i pos = sfMouse_getPositionRenderWindow(win->window);
    sfFloatRect rect;

    for (int i = 1; i < 9; i++) {
        rect = sfRectangleShape_getGlobalBounds(inv->rect[i]);
        if (sfFloatRect_contains(&rect, pos.x, pos.y))
            printf("here\n");
    }
}

static void check_inventory(wolf_t *wolf, sfEvent event, inv_t *inv)
{
    if (sfMouse_isButtonPressed(sfMouseLeft))
        manage_inventory(wolf->window_data, inv);
}

void open_inventory(wolf_t *wolf, sfEvent event, inv_t *inv)
{
    if (iskeypressed(sfKeyE, event)) {
        inv->open = !inv->open;
        sfRenderWindow_setMouseCursorVisible(wolf->window_data->window,
            inv->open ? sfTrue : sfFalse);
        sfMouse_setPositionRenderWindow((sfVector2i){wolf->window_data->width
                / 2, wolf->window_data->height / 2}, wolf->window_data->window);
    }
    if (inv->open)
        check_inventory(wolf, event, inv);
}
