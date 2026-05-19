/*
** EPITECH PROJECT, 2026
** init
** File description:
** settings text initialization
*/

#include "../../include/wolf3d.h"

static void create_setting_triangles_for_state(window_t *window, float y,
    int state, triangle_t **triangles)
{
    triangles[0] = create_triangle(&(triangle_t){NULL, "left_value", state,
            TYPE_SETTINGS}, &(sfVector2f){window->width / 2.5f, y},
        (sfVector2f[3]){{-15, 0}, {0, 15}, {0, -15}});
    triangles[1] = create_triangle(&(triangle_t){NULL, "right_value", state,
            TYPE_SETTINGS}, &(sfVector2f){window->width * 0.6f, y},
        (sfVector2f[3]){{15, 0}, {0, 15}, {0, -15}});
}

void init_setting_value(wolf_t *wolf, text_t *data, float y, int state)
{
    triangle_t *triangles[2] = {NULL, NULL};
    text_t *text = NULL;

    create_setting_triangles_for_state(wolf->window_data, y, state, triangles);
    text = create_text(data, wolf->data->font,
        &(sfVector2f){wolf->window_data->width / 2.0f, y},
        &(sfVector2f){1.1f, 1.1f});
    if (text) {
        text->left_triangle = triangles[0];
        text->right_triangle = triangles[1];
    }
    center_text_on_screen(text, wolf->window_data, y);
    if (text)
        push_front(&wolf->list[SETTINGS][TEXT], text);
    push_double_arrow(wolf, triangles);
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

static void init_graphics_entry(wolf_t *wolf, window_t *window,
    setting_entry_t *entry)
{
    push_front(&wolf->list[SETTINGS][TEXT],
        create_text(&(text_t){entry->name, entry->content, GRAPHICS,
                TYPE_SETTINGS, NULL, sfFalse, NULL, NULL}, wolf->data->font,
            &(sfVector2f){window->width / 7,
                window->height / 2.9f + 80 * entry->index},
            &(sfVector2f){1.1f, 1.1f}));
    push_front(&wolf->list[SETTINGS][LINE],
        create_line(&(rect_t){entry->name, GRAPHICS, NULL, NULL, NULL,
                TYPE_SETTINGS, sfFalse},
            &(sfVector2f){window->width / 7 - 11,
                window->height / 2.9f + 80 * entry->index + 40},
            &(sfVector2f){window->width / 1.5f, 1.0f}));
}

void init_graphics(wolf_t *wolf, window_t *window)
{
    setting_entry_t entries[] = {
        {"resolution", "RESOLUTION", NULL, 0, 0},
        {"fullscreen", "FULLSCREEN", NULL, 0, 1},
        {"vsync", "V-SYNC", NULL, 0, 2},
        {"fov", "FOV", NULL, 0, 3},
        {"brightness", "BRIGHTNESS", NULL, 0, 4},
        {"max_fps", "MAX FPS", NULL, 0, 5}
    };
    int i = 0;

    for (i = 0; i < 6; i++)
        init_graphics_entry(wolf, window, &entries[i]);
}

void init_setting_text_value(wolf_t *wolf, setting_entry_t *entry,
    int state)
{
    text_t data;
    float y = wolf->window_data->height / 2.9f + 80 * entry->index;

    data = (text_t){entry->value_name, entry->content, state, TYPE_SETTINGS,
        NULL, sfFalse, NULL, NULL};
    init_setting_value(wolf, &data, y, state);
}

void init_setting_number_value(wolf_t *wolf, setting_entry_t *entry,
    int state)
{
    char *value_str = my_nbr_to_str(entry->value);

    if (!value_str)
        return;
    entry->content = value_str;
    init_setting_text_value(wolf, entry, state);
    free(value_str);
}
