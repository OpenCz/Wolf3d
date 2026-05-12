/*
** EPITECH PROJECT, 2026
** ~/Epitech/Project/Wolf3d/src/settings
** File description:
** settings_buttons
*/

#include "wolf3d.h"

static void center_text_on_rect(sfText *text, sfRectangleShape *rect)
{
    sfFloatRect text_bounds = sfText_getLocalBounds(text);
    sfFloatRect rect_bounds = sfRectangleShape_getGlobalBounds(rect);

    sfText_setOrigin(text, (sfVector2f){
            text_bounds.left + text_bounds.width / 2.0f,
            text_bounds.top + text_bounds.height / 2.0f});
    sfText_setPosition(text, (sfVector2f){
            rect_bounds.left + rect_bounds.width / 2.0f,
            rect_bounds.top + rect_bounds.height / 2.0f});
}

static void create_settings_box(wolf_t *wolf, sfVector2f *pos, text_t *info,
    sfVector2f *size)
{
    const char *texture = size->x > 300.0f ? "assets/settings_button.png"
        : "assets/settings_button_click.png";
    rect_t *rect = create_rectangles(&(rect_t){(char *)info->name, info->state,
            NULL, NULL, NULL, TYPE_SETTINGS, sfTrue}, texture, pos, size);
    text_t *text = create_text(info, wolf->data->font, pos,
        &(sfVector2f){1.0f, 1.0f});

    if (!rect || !text)
        return;
    sfText_setCharacterSize(text->text, 28);
    center_text_on_rect(text->text, rect->rect);
    push_front(&wolf->list[SETTINGS][RECT], rect);
    push_front(&wolf->list[SETTINGS][TEXT], text);
}

static void create_settings_title(wolf_t *wolf, float x, float y, text_t *info)
{
    sfVector2f pos = (sfVector2f){x, y};
    text_t *text = create_text(info, wolf->data->font, &pos,
        &(sfVector2f){3.0f, 3.0f});

    if (!text)
        return;
    sfText_setColor(text->text, sfColor_fromRGB(247, 167, 3));
    push_front(&wolf->list[SETTINGS][TEXT], text);
}

static void create_settings(wolf_t *wolf, text_t *infos, window_t *window)
{
    float start_x = (window->width - (5 * 300.0f)) / 2.0f + 150.0f;
    float y = window->height / 4.8f;
    float second_y = window->height / 1.25f;

    for (int i = 0; i < 9; i++) {
        if (i == 8)
            create_settings_title(wolf, window->width / 2.5f,
                window->height / 3.7f, &infos[i]);
        if (i < 5)
            create_settings_box(wolf,
                &(sfVector2f){start_x + i * 300.0f, y}, &infos[i],
                &(sfVector2f){280.0f, 70.0f});
        if (i >= 5 && i < 8)
            create_settings_box(wolf,
                &(sfVector2f){start_x + 150.0f + (i - 5) * 450.0f, second_y},
                &infos[i], &(sfVector2f){380.0f, 70.0f});
    }
}

void init_settings_buttons(wolf_t *wolf, window_t *window)
{
    char *names[] = {"graphics", "audio", "gameplay", "controls",
        "accessibility", "reset", "back", "apply", "settings"};
    char *contents[] = {"GRAPHICS", "AUDIO", "GAMEPLAY", "CONTROLS",
        "ACCESSIBILITY", "RESET TO DEFAULT", "BACK", "APPLY", "SETTINGS"};
    int states[] = {GRAPHICS, AUDIO, GAMEPLAY, CONTROLS, ACCESSIBILITY,
        -1, -1, -1, -1};
    text_t infos[9];

    for (int i = 0; i < 9; i++)
        infos[i] = (text_t){names[i], contents[i], states[i], TYPE_SETTINGS,
            NULL, sfTrue, NULL, NULL};
    create_settings(wolf, infos, window);
}
