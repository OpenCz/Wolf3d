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

int in_list_top(char *name)
{
    char *names[] = {"graphics", "audio", "gameplay", "controls",
        "accessibility"};

    for (int i = 0; i < 5; i++) {
        if (strcmp(name, names[i]) == 0)
            return 0;
    }
    return 84;
}

int in_list_bottom(char *name)
{
    char *names[] = {"reset", "back", "apply"};

    for (int i = 0; i < 3; i++) {
        if (strcmp(name, names[i]) == 0)
            return 0;
    }
    return 84;
}

void draw_text_list(wolf_t *wolf)
{
    text_t *text = NULL;

    for (list_t *c = wolf->list[wolf->state][TEXT]; c; c = c->next) {
        text = (text_t *)c->data;
        sfText_setColor(text->text, sfWhite);
        if (wolf->menu_state == text->state && text->type == TYPE_MENU)
            sfText_setColor(text->text, sfRed);
        if (text->type == TYPE_MENU)
            sfRenderWindow_drawText(wolf->window_data->window, text->text,
                NULL);
        if (text->type == TYPE_SETTINGS && (in_list_top(text->name) == 0
             || in_list_bottom(text->name) == 0))
            sfRenderWindow_drawText(wolf->window_data->window, text->text,
                NULL);
        if (wolf->settings_state == text->state
            && text->state == wolf->settings_state)
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
        if (wolf->settings_state == rect->state
            && rect->type == TYPE_SETTINGS && (in_list_top(rect->name) == 0
            || in_list_bottom(rect->name) == 0)) {
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
        sfRenderWindow_drawRectangleShape(wolf->window_data->window,
            line->rect, NULL);
    }
}
