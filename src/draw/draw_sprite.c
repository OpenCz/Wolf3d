/*
** EPITECH PROJECT, 2026
** draw
** File description:
** decor
*/

#include "../../include/wolf3d.h"

void draw_sprite_list(wolf_t *wolf)
{
    entity_t *entity = NULL;

    for (list_t *c = wolf->list[wolf->state][SPRITE]; c; c = c->next) {
        entity = (entity_t *)c->data;
        sfRenderWindow_drawSprite(wolf->window_data->window,
            entity->sprite, NULL);
    }
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
}

void draw_rect_list(wolf_t *wolf)
{
    rect_t *rect = NULL;

    for (list_t *c = wolf->list[wolf->state][RECT]; c; c = c->next) {
        rect = (rect_t *)c->data;
        sfRenderWindow_drawRectangleShape(wolf->window_data->window, rect->rect, NULL);
    }
}
