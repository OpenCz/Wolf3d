/*
** EPITECH PROJECT, 2026
** draw
** File description:
** decor
*/

#include "../../include/wolf3d.h"

void draw_inventory(wolf_t *wolf, sfRenderWindow *win, inv_t *inv)
{
    if (wolf->state != GAME || wolf->game->inv.open != sfTrue)
        return;
    sfRenderWindow_drawRectangleShape(win, wolf->game->inv.rect[9], NULL);
    for (int i = 0; i < 9; i++) {
        sfRenderWindow_drawRectangleShape(win,
            wolf->game->inv.rect[i], NULL);
        if (i == 0)
            continue;
        draw_inventory_item(wolf->window_data, &wolf->game->inv, i);
        sfRectangleShape_setFillColor(inv->rect[i], inv->slot[i - 1].selected ?
            (sfColor){200, 50, 50, 150} : sfWhite);
    }
}

void draw_sprite_list(wolf_t *wolf)
{
    entity_t *entity = NULL;
    sfRenderWindow *win = wolf->window_data->window;

    for (list_t *c = wolf->list[wolf->state][SPRITE]; c; c = c->next) {
        entity = (entity_t *)c->data;
        sfRenderWindow_drawSprite(wolf->window_data->window,
            entity->sprite, NULL);
    }
    draw_inventory(wolf, win, &wolf->game->inv);
}

void draw_text_list(wolf_t *wolf)
{
    text_t *text = NULL;

    for (list_t *c = wolf->list[wolf->state][TEXT]; c; c = c->next) {
        text = (text_t *)c->data;
        sfText_setColor(text->text, sfWhite);
        if (wolf->menu_state == text->state)
            sfText_setColor(text->text, sfRed);
        sfRenderWindow_drawText(wolf->window_data->window, text->text, NULL);
    }
    draw_selected_item(wolf->window_data, &wolf->game->inv);
}
