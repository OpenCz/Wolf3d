/*
** EPITECH PROJECT, 2026
** menu
** File description:
** menu
*/

#include "../../include/wolf3d.h"

void menu(wolf_t *wolf)
{
    text_t *text;

    for (list_t *c = wolf->list[MENU][TEXT]; c; c = c->next) {
        text = (text_t *)c->data;
        sfText_setColor(text->text, sfWhite);
        if (wolf->menu_state == text->state)
            sfText_setColor(text->text, sfRed);
    }
}
