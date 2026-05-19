/*
** EPITECH PROJECT, 2026
** main
** File description:
** event check
*/

#include "../include/wolf3d.h"

void check_event(sfRenderWindow *window, sfEvent event, wolf_t *wolf)
{
    if (event.type == sfEvtClosed || wolf->state == QUIT)
        sfRenderWindow_close(window);
    switch (wolf->state) {
        case MENU:
            manage_menu(wolf, event);
            break;
        case GAME:
            break;
        case SETTINGS:
            manage_settings(wolf, event);
            break;
        default:
            break;
    }
}

