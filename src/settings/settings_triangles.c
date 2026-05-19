/*
** EPITECH PROJECT, 2026
** ~/Epitech/Project/Wolf3d/src/settings
** File description:
** settings_triangles
*/

#include "wolf3d.h"

static const int_range_t RANGE_PERCENT = {0, 100, 5};
static const int_range_t RANGE_FOV = {40, 120, 5};
static const int_range_t RANGE_SENS = {10, 100, 5};

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

static int find_resolution_index(const sfVideoMode *mode)
{
    sfVideoMode resolutions[] = {{800, 600, 32}, {1280, 720, 32},
        {1600, 900, 32}, {1920, 1080, 32}};
    int i = 0;

    for (i = 0; i < 4; i++)
        if (resolutions[i].width == mode->width
            && resolutions[i].height == mode->height)
            return i;
    return 2;
}

static void update_resolution_value(wolf_t *wolf, text_t *text, int direction)
{
    sfVideoMode resolutions[] = {{800, 600, 32}, {1280, 720, 32},
        {1600, 900, 32}, {1920, 1080, 32}};
    int idx = find_resolution_index(&wolf->tmp_settings->resolution);
    char *buffer;
    int size;

    idx = (idx + direction + 4) % 4;
    wolf->tmp_settings->resolution = resolutions[idx];
    size = snprintf(NULL, 0, "%u x %u",
        wolf->tmp_settings->resolution.width,
        wolf->tmp_settings->resolution.height) + 1;
    buffer = malloc(size);
    if (!buffer)
        return;
    snprintf(buffer, size, "%u x %u",
        wolf->tmp_settings->resolution.width,
        wolf->tmp_settings->resolution.height);
    sfText_setString(text->text, buffer);
    recenter_text(text->text);
    free(buffer);
}

static void update_toggle_value(text_t *text, sfBool *value)
{
    *value = !(*value);
    sfText_setString(text->text, *value ? "ON" : "OFF");
    recenter_text(text->text);
}

static void update_int_value(text_t *text, int *value, int direction,
    const int_range_t *range)
{
    int next = *value + range->step * direction;
    char *buffer;

    if (next < range->min)
        next = range->min;
    if (next > range->max)
        next = range->max;
    *value = next;
    buffer = my_nbr_to_str(*value);
    if (!buffer)
        return;
    sfText_setString(text->text, buffer);
    recenter_text(text->text);
    free(buffer);
}

static void update_max_fps_value(wolf_t *wolf, text_t *text, int direction)
{
    int fps_values[] = {30, 60, 75, 120, 144, 165, 240};
    int idx = 0;
    char *buffer;
    int size;
    int i = 0;

    for (i = 0; i < 7; i++)
        if (fps_values[i] == wolf->tmp_settings->max_fps)
            idx = i;
    idx = (idx + direction + 7) % 7;
    wolf->tmp_settings->max_fps = fps_values[idx];
    size = snprintf(NULL, 0, "%d", wolf->tmp_settings->max_fps) + 1;
    buffer = malloc(size);
    if (!buffer)
        return;
    snprintf(buffer, size, "%d", wolf->tmp_settings->max_fps);
    sfText_setString(text->text, buffer);
    recenter_text(text->text);
    free(buffer);
}

static void apply_graphics_action(wolf_t *wolf, text_t *text, int direction)
{
    if (strcmp(text->name, "resolution_value") == 0)
        update_resolution_value(wolf, text, direction);
    if (strcmp(text->name, "fullscreen_value") == 0)
        update_toggle_value(text, &wolf->tmp_settings->fullscreen);
    if (strcmp(text->name, "max_fps_value") == 0)
        update_max_fps_value(wolf, text, direction);
    if (strcmp(text->name, "vsync_value") == 0)
        update_toggle_value(text, &wolf->tmp_settings->vsync);
    if (strcmp(text->name, "fov_value") == 0)
        update_int_value(text, &wolf->tmp_settings->fov, direction,
            &RANGE_FOV);
    if (strcmp(text->name, "brightness_value") == 0)
        update_int_value(text, &wolf->tmp_settings->brightness, direction,
            &RANGE_PERCENT);
}

static void apply_audio_action(wolf_t *wolf, text_t *text, int direction)
{
    if (strcmp(text->name, "master_volume_value") == 0)
        update_int_value(text, &wolf->tmp_settings->master_volume, direction,
            &RANGE_PERCENT);
    if (strcmp(text->name, "music_volume_value") == 0)
        update_int_value(text, &wolf->tmp_settings->music_volume, direction,
            &RANGE_PERCENT);
    if (strcmp(text->name, "sfx_volume_value") == 0)
        update_int_value(text, &wolf->tmp_settings->sfx_volume, direction,
            &RANGE_PERCENT);
    if (strcmp(text->name, "ambient_volume_value") == 0)
        update_int_value(text, &wolf->tmp_settings->ambient_volume, direction,
            &RANGE_PERCENT);
}

static void apply_gameplay_action(wolf_t *wolf, text_t *text, int direction)
{
    if (strcmp(text->name, "mouse_sensitivity_value") == 0)
        update_int_value(text, &wolf->tmp_settings->mouse_sensitivity,
            direction, &RANGE_SENS);
    if (strcmp(text->name, "invert_mouse_value") == 0)
        update_toggle_value(text, &wolf->tmp_settings->invert_mouse);
    if (strcmp(text->name, "show_hud_value") == 0)
        update_toggle_value(text, &wolf->tmp_settings->show_hud);
    if (strcmp(text->name, "show_fps_value") == 0)
        update_toggle_value(text, &wolf->tmp_settings->show_fps);
    if (strcmp(text->name, "show_minimap_value") == 0)
        update_toggle_value(text, &wolf->tmp_settings->show_minimap);
    if (strcmp(text->name, "crosshair_value") == 0)
        update_toggle_value(text, &wolf->tmp_settings->crosshair);
}

void apply_triangle_action(wolf_t *wolf, text_t *text, int direction)
{
    if (!text || text->type != TYPE_SETTINGS)
        return;
    apply_graphics_action(wolf, text, direction);
    apply_audio_action(wolf, text, direction);
    apply_gameplay_action(wolf, text, direction);
}

