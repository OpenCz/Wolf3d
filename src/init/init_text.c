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

void init_menu_text(wolf_t *wolf, window_t *window)
{
    push_front(&wolf->list[MENU][TEXT],
        create_text(&(text_t){"ng_btn", "NEW GAME", NEWGAME, TYPE_MENU, NULL,
                sfTrue, NULL, NULL}, wolf->data->font,
            &(sfVector2f){window->width / 10, window->height / 2.2},
            &(sfVector2f){1.5f, 1.5f}));
    push_front(&wolf->list[MENU][TEXT],
        create_text(&(text_t){"continue_btn", "CONTINUE", CONTINUE, TYPE_MENU,
                NULL, sfTrue, NULL, NULL}, wolf->data->font,
            &(sfVector2f){window->width / 10, window->height / 2.2 + 90},
            &(sfVector2f){1.5f, 1.5f}));
    push_front(&wolf->list[MENU][TEXT],
        create_text(&(text_t){"option_btn", "OPTIONS", OPTIONS, TYPE_MENU,
                NULL, sfTrue, NULL, NULL}, wolf->data->font,
            &(sfVector2f){window->width / 10, window->height / 2.2 + 90 * 2},
            &(sfVector2f){1.5f, 1.5f}));
    push_front(&wolf->list[MENU][TEXT],
        create_text(&(text_t){"option_btn", "LEAVE", LEAVE, TYPE_MENU, NULL,
                sfTrue, NULL, NULL}, wolf->data->font,
            &(sfVector2f){window->width / 10, window->height / 2.2 + 90 * 3},
            &(sfVector2f){1.5f, 1.5f}));
}

void init_graphics(wolf_t *wolf, window_t *window)
{
    char *names[] = {"resolution", "fullscreen", "vsync", "fov", "brightness",
        "max_fps"};
    char *contents[] = {"RESOLUTION", "FULLSCREEN", "V-SYNC", "FOV",
        "BRIGHTNESS", "MAX FPS"};

    for (int i = 0; i < 6; i++) {
        push_front(&wolf->list[SETTINGS][TEXT],
            create_text(&(text_t){names[i], contents[i], GRAPHICS,
                    TYPE_SETTINGS, NULL, sfFalse, NULL, NULL},
                wolf->data->font,
                &(sfVector2f){window->width / 7,
                    window->height / 2.9f + 80 * i},
                &(sfVector2f){1.1f, 1.1f}));
        push_front(&wolf->list[SETTINGS][LINE],
            create_line(&(rect_t){names[i], GRAPHICS, NULL, NULL, NULL,
                    TYPE_SETTINGS, sfFalse},
                &(sfVector2f){window->width / 7 - 11,
                    window->height / 2.9f + 80 * i + 40},
                &(sfVector2f){window->width / 1.5f, 1.0f}));
    }
}

void init_audio(wolf_t *wolf, window_t *window)
{
    char *names[] = {"master_volume", "music_volume", "sfx_volume",
        "ambient_volume"};
    char *contents[] = {"MASTER VOLUME", "MUSIC VOLUME", "SFX VOLUME",
        "AMBIENT VOLUME"};

    for (int i = 0; i < 4; i++) {
        push_front(&wolf->list[SETTINGS][TEXT],
            create_text(&(text_t){names[i], contents[i], AUDIO,
                    TYPE_SETTINGS, NULL, sfFalse, NULL, NULL},
                wolf->data->font,
                &(sfVector2f){window->width / 7,
                    window->height / 2.9f + 80 * i},
                &(sfVector2f){1.1f, 1.1f}));
        push_front(&wolf->list[SETTINGS][LINE],
            create_line(&(rect_t){names[i], AUDIO, NULL, NULL, NULL,
                    TYPE_SETTINGS, sfFalse},
                &(sfVector2f){window->width / 7 - 11,
                    window->height / 2.9f + 80 * i + 40},
                &(sfVector2f){window->width / 1.5f, 1.0f}));
    }
}

void init_gameplay(wolf_t *wolf, window_t *window)
{
    char *names[] = {"mouse_sensitivity", "invert_mouse", "show_hud",
        "show_fps", "show_minimap", "crosshair"};
    char *contents[] = {"MOUSE SENSITIVITY", "INVERT MOUSE", "SHOW HUD",
        "SHOW FPS", "SHOW MINIMAP", "CROSSHAIR"};

    for (int i = 0; i < 6; i++) {
        push_front(&wolf->list[SETTINGS][TEXT],
            create_text(&(text_t){names[i], contents[i], GAMEPLAY,
                    TYPE_SETTINGS, NULL, sfFalse, NULL, NULL},
                wolf->data->font,
                &(sfVector2f){window->width / 7,
                    window->height / 2.9f + 80 * i},
                &(sfVector2f){1.1f, 1.1f}));
        push_front(&wolf->list[SETTINGS][LINE],
            create_line(&(rect_t){names[i], GAMEPLAY, NULL, NULL, NULL,
                    TYPE_SETTINGS, sfFalse},
                &(sfVector2f){window->width / 7 - 11,
                    window->height / 2.9f + 80 * i + 40},
                &(sfVector2f){window->width / 1.5f, 1.0f}));
    }
}
