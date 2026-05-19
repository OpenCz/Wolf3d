/*
** EPITECH PROJECT, 2026
** ~/Epitech/Project/Wolf3d/src/settings
** File description:
** settings
*/

#include "wolf3d.h"

static void recenter_text(sfText *text)
{
    sfFloatRect bounds;
    sfVector2f pos;

    if (!text)
        return;
    pos = sfText_getPosition(text);
    bounds = sfText_getLocalBounds(text);
    sfText_setOrigin(text, (sfVector2f){bounds.left + bounds.width / 2.0f,
            bounds.top + bounds.height / 2.0f});
    sfText_setPosition(text, pos);
}

static text_t *find_settings_text(wolf_t *wolf, const char *name)
{
    text_t *text = NULL;

    if (!wolf || !name)
        return NULL;
    for (list_t *c = wolf->list[SETTINGS][TEXT]; c; c = c->next) {
        text = (text_t *)c->data;
        if (!text || !text->name)
            continue;
        if (strcmp(text->name, name) == 0)
            return text;
    }
    return NULL;
}

static void set_text_string(text_t *text, const char *value)
{
    if (!text || !text->text || !value)
        return;
    sfText_setString(text->text, value);
    recenter_text(text->text);
}

static void set_text_int(text_t *text, int value)
{
    char *buffer = my_nbr_to_str(value);

    if (!buffer)
        return;
    set_text_string(text, buffer);
    free(buffer);
}

static void set_text_resolution(text_t *text, sfVideoMode *mode)
{
    int size = snprintf(NULL, 0, "%u x %u", mode->width, mode->height) + 1;
    char *buffer = malloc(size);

    if (!buffer)
        return;
    snprintf(buffer, size, "%u x %u", mode->width, mode->height);
    set_text_string(text, buffer);
    free(buffer);
}

static void sync_graphics_values(wolf_t *wolf, settings_game_t *settings)
{
    set_text_resolution(find_settings_text(wolf, "resolution_value"),
        &settings->resolution);
    set_text_string(find_settings_text(wolf, "fullscreen_value"),
        settings->fullscreen ? "ON" : "OFF");
    set_text_string(find_settings_text(wolf, "vsync_value"),
        settings->vsync ? "ON" : "OFF");
    set_text_int(find_settings_text(wolf, "fov_value"), settings->fov);
    set_text_int(find_settings_text(wolf, "brightness_value"),
        settings->brightness);
    set_text_int(find_settings_text(wolf, "max_fps_value"),
        settings->max_fps);
}

static void sync_audio_values(wolf_t *wolf, settings_game_t *settings)
{
    set_text_int(find_settings_text(wolf, "master_volume_value"),
        settings->master_volume);
    set_text_int(find_settings_text(wolf, "music_volume_value"),
        settings->music_volume);
    set_text_int(find_settings_text(wolf, "sfx_volume_value"),
        settings->sfx_volume);
    set_text_int(find_settings_text(wolf, "ambient_volume_value"),
        settings->ambient_volume);
}

static void sync_gameplay_values(wolf_t *wolf, settings_game_t *settings)
{
    set_text_int(find_settings_text(wolf, "mouse_sensitivity_value"),
        settings->mouse_sensitivity);
    set_text_string(find_settings_text(wolf, "invert_mouse_value"),
        settings->invert_mouse ? "ON" : "OFF");
    set_text_string(find_settings_text(wolf, "show_hud_value"),
        settings->show_hud ? "ON" : "OFF");
    set_text_string(find_settings_text(wolf, "show_fps_value"),
        settings->show_fps ? "ON" : "OFF");
    set_text_string(find_settings_text(wolf, "show_minimap_value"),
        settings->show_minimap ? "ON" : "OFF");
    set_text_string(find_settings_text(wolf, "crosshair_value"),
        settings->crosshair ? "ON" : "OFF");
}

static void sync_settings_values(wolf_t *wolf, settings_game_t *settings)
{
    if (!wolf || !settings)
        return;
    sync_graphics_values(wolf, settings);
    sync_audio_values(wolf, settings);
    sync_gameplay_values(wolf, settings);
}

void reset_settings(wolf_t *wolf)
{
    settings_game_t *defaults = NULL;

    if (!wolf || !wolf->tmp_settings)
        return;
    defaults = init_settings_params();
    if (!defaults)
        return;
    memcpy(wolf->tmp_settings, defaults, sizeof(settings_game_t));
    free(defaults);
    sync_settings_values(wolf, wolf->tmp_settings);
}

void settings(wolf_t *wolf)
{
    (void)wolf;
}
