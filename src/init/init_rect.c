/*
** EPITECH PROJECT, 2026
** ~/Epitech/Project/Wolf3d/src/init
** File description:
** init_rectangle
*/

#include "wolf3d.h"

static void set_param(rect_t *rect, sfVector2f *scale, sfVector2f *pos)
{
    sfFloatRect rect_txt;

    sfRectangleShape_setSize(rect->rect, *scale);
    rect_txt = sfRectangleShape_getGlobalBounds(rect->rect);
    sfRectangleShape_setOrigin(rect->rect, (sfVector2f){rect_txt.width / 2,
            0});
    sfRectangleShape_setPosition(rect->rect, *pos);
    sfRectangleShape_setTexture(rect->rect, rect->texture, sfTrue);
}

static void free_rect(rect_t *rect)
{
    if (rect->name)
        free(rect->name);
    if (rect->texture)
        sfTexture_destroy(rect->texture);
    if (rect->click_texture)
        sfTexture_destroy(rect->click_texture);
    if (rect->rect)
        sfRectangleShape_destroy(rect->rect);
    free(rect);
}

rect_t *create_rectangles(rect_t *data, const char *texture_path,
    sfVector2f *pos, sfVector2f *scale)
{
    rect_t *rect = malloc(sizeof(rect_t));

    if (!rect)
        return NULL;
    rect->rect = sfRectangleShape_create();
    rect->name = data->name;
    rect->state = data->state;
    rect->type = data->type;
    rect->texture = sfTexture_createFromFile("assets/settings_button.png", NULL);
    rect->click_texture
    = sfTexture_createFromFile(texture_path, NULL);
    if (!rect->name || !rect->texture || !rect->click_texture) {
        free_rect(rect);
        return NULL;
    }
    set_param(rect, scale, pos);
    return rect;
}

rect_t *create_line(rect_t *data, sfVector2f *pos, sfVector2f *scale)
{
    rect_t *line = malloc(sizeof(rect_t));

    if (!line)
        return NULL;
    line->rect = sfRectangleShape_create();
    line->name = data->name;
    line->state = data->state;
    line->type = data->type;
    if (!line->name || !line->rect) {
        free_rect(line);
        return NULL;
    }
    sfRectangleShape_setSize(line->rect, (sfVector2f){1.0f, 1.0f});
    sfRectangleShape_setPosition(line->rect, *pos);
    sfRectangleShape_setFillColor(line->rect, sfColor_fromRGB(90, 75, 60));
    sfRectangleShape_setSize(line->rect, *scale);
    return line;
}
