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
        if (text->always_display == sfTrue)
            sfRenderWindow_drawText(wolf->window_data->window, text->text,
                NULL);
        if (wolf->menu_state == text->state && text->type == TYPE_MENU)
            sfText_setColor(text->text, sfRed);
        if (text->type == TYPE_MENU && wolf->menu_state != text->state)
            sfText_setColor(text->text, sfWhite);
        if (text->type == TYPE_MENU)
            sfRenderWindow_drawText(wolf->window_data->window, text->text,
                NULL);
        if (text->type == TYPE_SETTINGS && wolf->settings_state == text->state)
            sfRenderWindow_drawText(wolf->window_data->window, text->text,
                NULL);
    }
}

void draw_rect_list(wolf_t *wolf)
{
    rect_t *rect = NULL;

    for (list_t *c = wolf->list[wolf->state][RECT]; c; c = c->next) {
        rect = (rect_t *)c->data;
        sfRectangleShape_setScale(rect->rect, (sfVector2f){1.0f, 1.0f});
        if (rect->always_display == sfTrue)
            sfRenderWindow_drawRectangleShape(wolf->window_data->window,
                rect->rect, NULL);
        if (wolf->settings_state == rect->state) {
            sfRectangleShape_setScale(rect->rect, (sfVector2f){1.0f, 1.2f});
            sfRectangleShape_setTexture(rect->rect, rect->click_texture,
                sfTrue);
        } else
            sfRectangleShape_setTexture(rect->rect, rect->texture, sfTrue);
        sfRenderWindow_drawRectangleShape(wolf->window_data->window,
            rect->rect, NULL);
    }
}

void draw_line_list(wolf_t *wolf)
{
    rect_t *line = NULL;

    for (list_t *c = wolf->list[wolf->state][LINE]; c; c = c->next) {
        line = (rect_t *)c->data;
        if (!(wolf->state == SETTINGS && line->type == TYPE_SETTINGS
                && wolf->settings_state == line->state))
            continue;
        sfRenderWindow_drawRectangleShape(wolf->window_data->window,
            line->rect, NULL);
    }
}

void draw_triangle_list(wolf_t *wolf)
{
    triangle_t *triangle = NULL;

    for (list_t *c = wolf->list[wolf->state][TRIANGLE]; c; c = c->next) {
        triangle = (triangle_t *)c->data;
        if (!(wolf->state == SETTINGS && triangle->type == TYPE_SETTINGS
                && wolf->settings_state == triangle->state))
            continue;
        sfRenderWindow_drawConvexShape(wolf->window_data->window,
            triangle->shape, NULL);
    }
}
