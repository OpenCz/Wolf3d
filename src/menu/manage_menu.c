/*
** EPITECH PROJECT, 2026
** menu
** File description:
** menu
*/

#include "../../include/wolf3d.h"

sfBool iskeypressed(int key, sfEvent event)
{
    return (event.type == sfEvtKeyPressed && event.key.code == key);
}

void manage_menu(wolf_t *wolf, sfEvent event)
{
    window_t *win = wolf->window_data;

    if (iskeypressed(sfKeyEnter, event) && wolf->menu_state == NEWGAME) {
        sfMouse_setPositionRenderWindow((sfVector2i){win->width / 2,
                win->height / 2}, win->window);
        sfRenderWindow_setMouseCursorVisible(wolf->window_data->window,
            sfFalse);
        wolf->state = GAME;
    }
    if (iskeypressed(sfKeyEnter, event) && wolf->menu_state == LEAVE)
        sfRenderWindow_close(wolf->window_data->window);
    if (iskeypressed(sfKeyUp, event) && wolf->menu_state > 0)
        wolf->menu_state -= 1;
    if (iskeypressed(sfKeyDown, event) && wolf->menu_state < 3)
        wolf->menu_state += 1;
}
