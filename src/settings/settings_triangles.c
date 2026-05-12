/*
** EPITECH PROJECT, 2026
** ~/Epitech/Project/Wolf3d/src/settings
** File description:
** settings_triangles
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

static int find_resolution_index(const sfVideoMode *mode)
{
    sfVideoMode resolutions[] = {{800, 600, 32}, {1280, 720, 32},
        {1600, 900, 32}, {1920, 1080, 32}};

    for (int i = 0; i < 4; i++)
        if (resolutions[i].width == mode->width
            && resolutions[i].height == mode->height)
            return i;
    return 2;
}

static void update_resolution_value(wolf_t *wolf, text_t *text, int direction)
{
    sfVideoMode resolutions[] = {{800, 600, 32}, {1280, 720, 32},
        {1600, 900, 32}, {1920, 1080, 32}};
    int idx = find_resolution_index(&wolf->settings->resolution);
    char buffer[32];

    idx = (idx + direction + 4) % 4;
    wolf->settings->resolution = resolutions[idx];
    snprintf(buffer, sizeof(buffer), "%u x %u",
        wolf->settings->resolution.width, wolf->settings->resolution.height);
    sfText_setString(text->text, buffer);
    recenter_text(text->text);
}

static void update_toggle_value(text_t *text, sfBool *value)
{
    *value = !(*value);
    sfText_setString(text->text, *value ? "ON" : "OFF");
    recenter_text(text->text);
}

static void update_max_fps_value(wolf_t *wolf, text_t *text, int direction)
{
    int fps_values[] = {30, 60, 75, 120, 144, 165, 240};
    int idx = 0;
    char buffer[16];

    for (int i = 0; i < 7; i++)
        if (fps_values[i] == wolf->settings->max_fps)
            idx = i;
    idx = (idx + direction + 7) % 7;
    wolf->settings->max_fps = fps_values[idx];
    sfRenderWindow_setFramerateLimit(wolf->window_data->window,
        wolf->settings->max_fps);
    snprintf(buffer, sizeof(buffer), "%d", wolf->settings->max_fps);
    sfText_setString(text->text, buffer);
    recenter_text(text->text);
}

static void apply_triangle_action(wolf_t *wolf, text_t *text, int direction)
{
    if (!text || text->type != TYPE_SETTINGS)
        return;
    if (strcmp(text->name, "resolution_value") == 0)
        update_resolution_value(wolf, text, direction);
    if (strcmp(text->name, "fullscreen_value") == 0)
        update_toggle_value(text, &wolf->settings->fullscreen);
    if (strcmp(text->name, "max_fps_value") == 0)
        update_max_fps_value(wolf, text, direction);
    if (strcmp(text->name, "vsync_value") == 0) {
        update_toggle_value(text, &wolf->settings->vsync);
        sfRenderWindow_setVerticalSyncEnabled(wolf->window_data->window,
            wolf->settings->vsync);
    }
}

static sfBool click_one_triangle(text_t *text, sfEvent event, int direction)
{
    triangle_t *triangle = direction < 0 ? text->left_triangle
        : text->right_triangle;
    sfFloatRect bounds = sfConvexShape_getGlobalBounds(triangle->shape);

    return sfFloatRect_contains(&bounds, event.mouseButton.x,
        event.mouseButton.y);
}

sfBool click_settings_triangle(wolf_t *wolf, sfEvent event)
{
    text_t *text = NULL;

    for (list_t *c = wolf->list[SETTINGS][TEXT]; c; c = c->next) {
        text = (text_t *)c->data;
        if (!text || text->state != wolf->settings_state)
            continue;
        if (!text->left_triangle || !text->right_triangle)
            continue;
        if (click_one_triangle(text, event, -1)
            || click_one_triangle(text, event, 1)) {
            apply_triangle_action(wolf, text,
                click_one_triangle(text, event, -1) ? -1 : 1);
            return sfTrue;
        }
    }
    return sfFalse;
}

void hover_settings_triangle(wolf_t *wolf, sfEvent event)
{
    triangle_t *triangle = NULL;
    sfFloatRect bounds;

    for (list_t *c = wolf->list[SETTINGS][TRIANGLE]; c; c = c->next) {
        triangle = (triangle_t *)c->data;
        bounds = sfConvexShape_getGlobalBounds(triangle->shape);
        if (sfFloatRect_contains(&bounds, event.mouseMove.x,
                event.mouseMove.y))
            sfConvexShape_setFillColor(triangle->shape,
                sfColor_fromRGBA(138, 2, 0, 125));
        else
            sfConvexShape_setFillColor(triangle->shape,
                sfColor_fromRGBA(138, 2, 0, 255));
    }
}
