/*
** EPITECH PROJECT, 2026
** init
** File description:
** player
*/

#include "../../include/wolf3d.h"

static void set_param(text_t *text, sfVector2f *pos)
{
    sfText_setColor(text->text, sfWhite);
    sfText_setOutlineColor(text->text, sfBlack);
    sfText_setOutlineThickness(text->text, 1);
    sfText_setPosition(text->text, *pos);
}

text_t *create_text(text_t *data,
    sfFont *font, sfVector2f *pos, sfVector2f *scale)
{
    text_t *text = malloc(sizeof(text_t));
    sfFloatRect txt;

    if (!text)
        return NULL;
    text->text = sfText_create();
    text->name = data->name;
    text->content = data->content;
    text->state = data->state;
    text->type = data->type;
    sfText_setFont(text->text, font);
    sfText_setString(text->text, data->content);
    sfText_setScale(text->text, *scale);
    txt = sfText_getGlobalBounds(text->text);
    sfText_setOrigin(text->text, (sfVector2f){txt.left,
            txt.top + txt.height / 2});
    set_param(text, pos);
    return text;
}

void init_menu_text(wolf_t *wolf, window_t *window)
{
    push_front(&wolf->list[MENU][TEXT],
        create_text(&(text_t){"ng_btn", "NEW GAME", NEWGAME, TYPE_MENU, NULL},
            wolf->data->font,
            &(sfVector2f){window->width / 10, window->height / 2.2},
            &(sfVector2f){1.5f, 1.5f}));
    push_front(&wolf->list[MENU][TEXT],
        create_text(&(text_t){"continue_btn", "CONTINUE", CONTINUE, TYPE_MENU,
                NULL}, wolf->data->font,
            &(sfVector2f){window->width / 10, window->height / 2.2 + 90},
            &(sfVector2f){1.5f, 1.5f}));
    push_front(&wolf->list[MENU][TEXT],
        create_text(&(text_t){"option_btn", "OPTIONS", OPTIONS, TYPE_MENU,
                NULL}, wolf->data->font,
            &(sfVector2f){window->width / 10, window->height / 2.2 + 90 * 2},
            &(sfVector2f){1.5f, 1.5f}));
    push_front(&wolf->list[MENU][TEXT],
        create_text(&(text_t){"option_btn", "LEAVE", LEAVE, TYPE_MENU, NULL},
            wolf->data->font,
            &(sfVector2f){window->width / 10, window->height / 2.2 + 90 * 3},
            &(sfVector2f){1.5f, 1.5f}));
}
