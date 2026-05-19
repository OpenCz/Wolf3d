/*
** EPITECH PROJECT, 2026
** ~/EpitechProjects/Wolf3d/src/settings
** File description:
** apply
*/

#include "wolf3d.h"


static sfBool resolution_changed(settings_game_t *current,
    settings_game_t *next)
{
    if (!current || !next)
        return sfFalse;
    if (current->fullscreen != next->fullscreen)
        return sfTrue;
    if (current->resolution.width != next->resolution.width)
        return sfTrue;
    if (current->resolution.height != next->resolution.height)
        return sfTrue;
    return sfFalse;
}

static void update_crosshair(window_t *window, crosshair_t *crosshair)
{
    sfVector2f pos;

    if (!window || !crosshair || !crosshair->cursor)
        return;
    pos = (sfVector2f){window->width / 2.0f, window->height / 2.0f};
    crosshair->pos = pos;
    sfSprite_setPosition(crosshair->cursor->sprite, pos);
}

static sfBool allocate_resize_buffers(wolf_t *wolf, resize_buffers_t *buffers)
{
    size_t pixel_size;

    if (!wolf || !wolf->game || !wolf->game->wall || !wolf->window_data
        || !buffers)
        return sfFalse;
    pixel_size = (size_t)wolf->window_data->width *
        (size_t)wolf->window_data->height * 4;
    buffers->pixel = malloc(pixel_size);
    buffers->zbuffer = malloc(sizeof(float) *
        (size_t)wolf->window_data->width);
    buffers->texture = sfTexture_create(wolf->window_data->width,
        wolf->window_data->height);
    if (!buffers->pixel || !buffers->zbuffer || !buffers->texture) {
        free(buffers->pixel);
        free(buffers->zbuffer);
        if (buffers->texture)
            sfTexture_destroy(buffers->texture);
        return sfFalse;
    }
    return sfTrue;
}

static void apply_resize_buffers(wolf_t *wolf, resize_buffers_t *buffers)
{
    if (!wolf || !wolf->game || !wolf->game->wall || !buffers)
        return;
    free(wolf->game->wall->pixel);
    wolf->game->wall->pixel = buffers->pixel;
    free(wolf->game->zbuffer);
    wolf->game->zbuffer = buffers->zbuffer;
    sfTexture_destroy(wolf->game->wall->texture);
    wolf->game->wall->texture = buffers->texture;
    sfSprite_setTexture(wolf->game->wall->sprite, buffers->texture, sfTrue);
    update_crosshair(wolf->window_data, &wolf->game->crosshair);
}

static void resize_game_buffers(wolf_t *wolf)
{
    resize_buffers_t buffers = {0};

    if (!allocate_resize_buffers(wolf, &buffers))
        return;
    apply_resize_buffers(wolf, &buffers);
}

static void recreate_window(wolf_t *wolf)
{
    sfUint32 style;
    sfRenderWindow *new_window;

    if (!wolf || !wolf->window_data)
        return;
    style = wolf->settings->fullscreen ? sfFullscreen : sfClose;
    new_window = sfRenderWindow_create(wolf->settings->resolution,
        "Wolf3D", style, NULL);
    if (!new_window)
        return;
    sfRenderWindow_destroy(wolf->window_data->window);
    wolf->window_data->window = new_window;
    wolf->window_data->width = wolf->settings->resolution.width;
    wolf->window_data->height = wolf->settings->resolution.height;
    resize_game_buffers(wolf);
}

void handle_window_recreate(wolf_t *wolf)
{
    int old_width;
    int old_height;

    if (!wolf || wolf->pending_window_recreate == sfFalse)
        return;
    wolf->pending_window_recreate = sfFalse;
    old_width = wolf->window_data->width;
    old_height = wolf->window_data->height;
    recreate_window(wolf);
    update_ui_layout(wolf, old_width, old_height);
}

void apply_settings(wolf_t *wolf)
{
    sfBool need_window_recreate = sfFalse;

    if (!wolf || !wolf->settings || !wolf->tmp_settings || !wolf->window_data)
        return;
    need_window_recreate = resolution_changed(wolf->settings,
        wolf->tmp_settings);
    memcpy(wolf->settings, wolf->tmp_settings, sizeof(settings_game_t));
    if (need_window_recreate)
        wolf->pending_window_recreate = sfTrue;
    sfRenderWindow_setVerticalSyncEnabled(wolf->window_data->window,
        wolf->settings->vsync);
    sfRenderWindow_setFramerateLimit(wolf->window_data->window,
        wolf->settings->max_fps);
}
