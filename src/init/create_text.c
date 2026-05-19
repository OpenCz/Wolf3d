/*
** EPITECH PROJECT, 2026
** init
** File description:
** text creation helpers
*/

#include "../../include/wolf3d.h"

static void set_param(text_t *text, sfVector2f *pos)
{
    sfText_setColor(text->text, sfWhite);
    sfText_setOutlineColor(text->text, sfBlack);
    sfText_setOutlineThickness(text->text, 1);
    sfText_setPosition(text->text, *pos);
}

static void setup_text_data(text_t *text, text_t *data)
{
    text->name = data->name;
    text->content = data->content;
    text->state = data->state;
    text->type = data->type;
    text->always_display = data->always_display;
    text->left_triangle = data->left_triangle;
    text->right_triangle = data->right_triangle;
}

text_t *create_text(text_t *data,
    sfFont *font, sfVector2f *pos, sfVector2f *scale)
{
    text_t *text = malloc(sizeof(text_t));
    sfFloatRect txt;

    if (!text)
        return NULL;
    text->text = sfText_create();
    setup_text_data(text, data);
    sfText_setFont(text->text, font);
    sfText_setString(text->text, data->content);
    sfText_setScale(text->text, *scale);
    txt = sfText_getGlobalBounds(text->text);
    sfText_setOrigin(text->text, (sfVector2f){txt.left,
            txt.top + txt.height / 2});
    set_param(text, pos);
    return text;
}
