/*
** EPITECH PROJECT, 2026
** init
** File description:
** audio and gameplay settings text initialization
*/

#include "../../include/wolf3d.h"

static const char *get_gameplay_toggle(wolf_t *wolf, int index)
{
    if (index == 1)
        return wolf->tmp_settings->invert_mouse ? "ON" : "OFF";
    if (index == 2)
        return wolf->tmp_settings->show_hud ? "ON" : "OFF";
    if (index == 3)
        return wolf->tmp_settings->show_fps ? "ON" : "OFF";
    if (index == 4)
        return wolf->tmp_settings->show_minimap ? "ON" : "OFF";
    if (index == 5)
        return wolf->tmp_settings->crosshair ? "ON" : "OFF";
    return "OFF";
}

static char *get_gameplay_value(wolf_t *wolf, int index)
{
    if (index == 0)
        return my_nbr_to_str(wolf->tmp_settings->mouse_sensitivity);
    return NULL;
}

static void init_setting_label(wolf_t *wolf, window_t *window,
    setting_entry_t *entry, int state)
{
    push_front(&wolf->list[SETTINGS][TEXT],
        create_text(&(text_t){entry->name, entry->content, state,
                TYPE_SETTINGS, NULL, sfFalse, NULL, NULL}, wolf->data->font,
            &(sfVector2f){window->width / 7,
                window->height / 2.9f + 80 * entry->index},
            &(sfVector2f){1.1f, 1.1f}));
}

static void init_setting_line(wolf_t *wolf, window_t *window,
    setting_entry_t *entry, int state)
{
    push_front(&wolf->list[SETTINGS][LINE],
        create_line(&(rect_t){entry->name, state, NULL, NULL, NULL,
                TYPE_SETTINGS, sfFalse},
            &(sfVector2f){window->width / 7 - 11,
                window->height / 2.9f + 80 * entry->index + 40},
            &(sfVector2f){window->width / 1.5f, 1.0f}));
}

static void init_setting_entry(wolf_t *wolf, window_t *window,
    setting_entry_t *entry, int state)
{
    init_setting_label(wolf, window, entry, state);
    init_setting_line(wolf, window, entry, state);
    if (state == AUDIO)
        init_setting_number_value(wolf, entry, state);
    else {
        entry->content = (char *)get_gameplay_toggle(wolf, entry->index);
        init_setting_text_value(wolf, entry, state);
    }
}

static void init_first_gameplay_value(wolf_t *wolf, window_t *window,
    setting_entry_t *entry)
{
    char *value_str = get_gameplay_value(wolf, 0);

    init_setting_label(wolf, window, entry, GAMEPLAY);
    init_setting_line(wolf, window, entry, GAMEPLAY);
    if (value_str) {
        entry->content = value_str;
        init_setting_text_value(wolf, entry, GAMEPLAY);
        free(value_str);
    }
}

void init_audio(wolf_t *wolf, window_t *window)
{
    setting_entry_t entries[] = {
        {"master_volume", "MASTER VOLUME", "master_volume_value",
            wolf->tmp_settings->master_volume, 0},
        {"music_volume", "MUSIC VOLUME", "music_volume_value",
            wolf->tmp_settings->music_volume, 1},
        {"sfx_volume", "SFX VOLUME", "sfx_volume_value",
            wolf->tmp_settings->sfx_volume, 2},
        {"ambient_volume", "AMBIENT VOLUME", "ambient_volume_value",
            wolf->tmp_settings->ambient_volume, 3}
    };
    int i = 0;

    for (i = 0; i < 4; i++)
        init_setting_entry(wolf, window, &entries[i], AUDIO);
}

void init_gameplay(wolf_t *wolf, window_t *window)
{
    setting_entry_t entries[] = {
        {"mouse_sensitivity", "MOUSE SENSITIVITY",
            "mouse_sensitivity_value", 0, 0},
        {"invert_mouse", "INVERT MOUSE", "invert_mouse_value", 1, 1},
        {"show_hud", "SHOW HUD", "show_hud_value", 2, 2},
        {"show_fps", "SHOW FPS", "show_fps_value", 3, 3},
        {"show_minimap", "SHOW MINIMAP", "show_minimap_value", 4, 4},
        {"crosshair", "CROSSHAIR", "crosshair_value", 5, 5}
    };
    int i = 0;

    init_first_gameplay_value(wolf, window, &entries[0]);
    for (i = 1; i < 6; i++)
        init_setting_entry(wolf, window, &entries[i], GAMEPLAY);
}
