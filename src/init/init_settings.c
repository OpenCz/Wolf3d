/*
** EPITECH PROJECT, 2026
** ~/EpitechProjects/Wolf3d/src/init
** File description:
** init_settings
*/

#include "wolf3d.h"

static void init_graphics_settings(settings_game_t *settings)
{
    settings->resolution = (sfVideoMode){1920, 1080, 32};
    settings->fullscreen = sfFalse;
    settings->vsync = sfTrue;
    settings->fov = 66;
    settings->brightness = 50;
    settings->max_fps = 144;
}

static void init_audio_settings(settings_game_t *settings)
{
    settings->master_volume = 80;
    settings->music_volume = 60;
    settings->sfx_volume = 90;
    settings->ambient_volume = 70;
}

static void init_gameplay_settings(settings_game_t *settings)
{
    settings->mouse_sensitivity = 50;
    settings->invert_mouse = sfFalse;
    settings->show_hud = sfTrue;
    settings->show_fps = sfFalse;
    settings->show_minimap = sfTrue;
    settings->crosshair = sfTrue;
}

settings_game_t *init_settings_params(void)
{
    settings_game_t *settings = malloc(sizeof(settings_game_t));

    if (!settings)
        return NULL;
    init_graphics_settings(settings);
    init_audio_settings(settings);
    init_gameplay_settings(settings);
    return settings;
}
