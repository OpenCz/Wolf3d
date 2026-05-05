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
    rect->texture = sfTexture_createFromFile(texture_path, NULL);
    rect->click_texture
    = sfTexture_createFromFile("assets/settings_button_click.png", NULL);
    if (!rect->name || !rect->texture || !rect->click_texture) {
        free_rect(rect);
        return NULL;
    }
    set_param(rect, scale, pos);
    return rect;
}
