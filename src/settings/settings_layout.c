/*
** EPITECH PROJECT, 2026
** ~/Epitech/Project/Wolf3d/src/settings
** File description:
** settings layout
*/

#include "wolf3d.h"

static void scale_sprite_list(list_t *list, float scale_x, float scale_y)
{
    entity_t *entity = NULL;
    sfVector2f pos;
    sfVector2f scale;

    while (list) {
        entity = (entity_t *)list->data;
        if (entity && entity->sprite) {
            pos = sfSprite_getPosition(entity->sprite);
            scale = sfSprite_getScale(entity->sprite);
            sfSprite_setPosition(entity->sprite,
                (sfVector2f){pos.x * scale_x, pos.y * scale_y});
            sfSprite_setScale(entity->sprite,
                (sfVector2f){scale.x * scale_x, scale.y * scale_y});
        }
        list = list->next;
    }
}

static void scale_text_list(list_t *list, float scale_x, float scale_y)
{
    text_t *text = NULL;
    sfVector2f pos;
    sfVector2f scale;

    while (list) {
        text = (text_t *)list->data;
        if (text && text->text) {
            pos = sfText_getPosition(text->text);
            scale = sfText_getScale(text->text);
            sfText_setPosition(text->text,
                (sfVector2f){pos.x * scale_x, pos.y * scale_y});
            sfText_setScale(text->text,
                (sfVector2f){scale.x * scale_x, scale.y * scale_y});
        }
        list = list->next;
    }
}

static void scale_rect_list(list_t *list, float scale_x, float scale_y)
{
    rect_t *rect = NULL;
    sfVector2f pos;
    sfVector2f size;

    while (list) {
        rect = (rect_t *)list->data;
        if (rect && rect->rect) {
            pos = sfRectangleShape_getPosition(rect->rect);
            size = sfRectangleShape_getSize(rect->rect);
            sfRectangleShape_setSize(rect->rect,
                (sfVector2f){size.x * scale_x, size.y * scale_y});
            sfRectangleShape_setOrigin(rect->rect,
                (sfVector2f){(size.x * scale_x) / 2.0f, 0.0f});
            sfRectangleShape_setPosition(rect->rect,
                (sfVector2f){pos.x * scale_x, pos.y * scale_y});
        }
        list = list->next;
    }
}

static void scale_line_list(list_t *list, float scale_x, float scale_y)
{
    rect_t *line = NULL;
    sfVector2f pos;
    sfVector2f size;

    while (list) {
        line = (rect_t *)list->data;
        if (line && line->rect) {
            pos = sfRectangleShape_getPosition(line->rect);
            size = sfRectangleShape_getSize(line->rect);
            sfRectangleShape_setSize(line->rect,
                (sfVector2f){size.x * scale_x, size.y * scale_y});
            sfRectangleShape_setPosition(line->rect,
                (sfVector2f){pos.x * scale_x, pos.y * scale_y});
        }
        list = list->next;
    }
}

static void scale_triangle_list(list_t *list, float scale_x, float scale_y)
{
    triangle_t *triangle = NULL;
    sfVector2f pos;

    while (list) {
        triangle = (triangle_t *)list->data;
        if (triangle && triangle->shape) {
            pos = sfConvexShape_getPosition(triangle->shape);
            sfConvexShape_setPosition(triangle->shape,
                (sfVector2f){pos.x * scale_x, pos.y * scale_y});
            sfConvexShape_scale(triangle->shape,
                (sfVector2f){scale_x, scale_y});
        }
        list = list->next;
    }
}

void update_ui_layout(wolf_t *wolf, int old_width, int old_height)
{
    float scale_x = 0.0f;
    float scale_y = 0.0f;
    int state = 0;

    if (!wolf || !wolf->window_data || old_width <= 0 || old_height <= 0)
        return;
    scale_x = (float)wolf->window_data->width / (float)old_width;
    scale_y = (float)wolf->window_data->height / (float)old_height;
    for (state = MENU; state <= SETTINGS; state++) {
        scale_sprite_list(wolf->list[state][SPRITE], scale_x, scale_y);
        scale_text_list(wolf->list[state][TEXT], scale_x, scale_y);
        scale_rect_list(wolf->list[state][RECT], scale_x, scale_y);
        scale_line_list(wolf->list[state][LINE], scale_x, scale_y);
        scale_triangle_list(wolf->list[state][TRIANGLE], scale_x, scale_y);
    }
}

