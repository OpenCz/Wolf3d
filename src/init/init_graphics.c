/*
** EPITECH PROJECT, 2026
** ~/EpitechProjects/Wolf3d/src/init
** File description:
** init_graphics
*/

#include "wolf3d.h"

static char *return_error(char *str1, char *str2)
{
    if (str1)
        free(str1);
    if (str2)
        free(str2);
    return NULL;
}

static char *get_resolution_string(sfVideoMode *mode)
{
    char *res_height = my_nbr_to_str(mode->height);
    char *res_width = my_nbr_to_str(mode->width);
    size_t len = 0;
    char *full_resolution = NULL;

    if (!res_height || !res_width)
        return return_error(res_width, res_height);
    len = strlen(res_width) + strlen(" x ") + strlen(res_height) + 1;
    full_resolution = malloc(len);
    if (!full_resolution)
        return return_error(res_width, res_height);
    strcpy(full_resolution, res_width);
    strcat(full_resolution, " x ");
    strcat(full_resolution, res_height);
    free(res_height);
    free(res_width);
    return full_resolution;
}

static void init_graphics_value(wolf_t *wolf, text_t *data, float y,
    sfBool with_triangles)
{
    triangle_t *triangles[2] = {NULL, NULL};
    text_t *text = NULL;

    if (with_triangles)
        create_setting_triangles(wolf->window_data, y, triangles);
    text = create_text(data, wolf->data->font,
        &(sfVector2f){wolf->window_data->width / 2.0f, y},
        &(sfVector2f){1.1f, 1.1f});
    if (text && with_triangles) {
        text->left_triangle = triangles[0];
        text->right_triangle = triangles[1];
    }
    center_text_on_screen(text, wolf->window_data, y);
    if (text)
        push_front(&wolf->list[SETTINGS][TEXT], text);
    if (with_triangles)
        push_double_arrow(wolf, triangles);
}

void init_resolution(wolf_t *wolf, window_t *window, sfVideoMode *mode, int y)
{
    char *full_resolution = get_resolution_string(mode);
    text_t data = {"resolution_value", full_resolution, GRAPHICS,
        TYPE_SETTINGS, NULL, sfFalse, NULL, NULL};

    if (!full_resolution)
        return;
    (void)window;
    init_graphics_value(wolf, &data, y, sfTrue);
    free(full_resolution);
}

static void init_fullscreen(wolf_t *wolf, window_t *window, int is_fullscreen)
{
    float y = window->height / 2.9f + 80;
    text_t data = {"fullscreen_value", is_fullscreen ? "ON" : "OFF",
        GRAPHICS, TYPE_SETTINGS, NULL, sfFalse, NULL, NULL};

    init_graphics_value(wolf, &data, y, sfTrue);
}

static void init_vsync(wolf_t *wolf, window_t *window, int is_vsync)
{
    float y = window->height / 2.9f + 160;
    text_t data = {"vsync_value", is_vsync ? "ON" : "OFF", GRAPHICS,
        TYPE_SETTINGS, NULL, sfFalse, NULL, NULL};

    init_graphics_value(wolf, &data, y, sfTrue);
}

static void init_fov(wolf_t *wolf, window_t *window, int fov)
{
    text_t *text = NULL;
    char *fov_str = my_nbr_to_str(fov);
    float y = window->height / 2.9f + 240;

    if (!fov_str)
        return;
    text = create_text(&(text_t){"fov_value", fov_str, GRAPHICS,
            TYPE_SETTINGS, NULL, sfFalse, NULL, NULL}, wolf->data->font,
        &(sfVector2f){window->width / 2.0f, y},
        &(sfVector2f){1.1f, 1.1f});
    center_text_on_screen(text, window, y);
    if (text)
        push_front(&wolf->list[SETTINGS][TEXT], text);
    free(fov_str);
}

static void init_brightness(wolf_t *wolf, window_t *window, int brightness)
{
    text_t *text = NULL;
    char *brightness_str = my_nbr_to_str(brightness);
    float y = window->height / 2.9f + 320;

    if (!brightness_str)
        return;
    text = create_text(&(text_t){"brightness_value", brightness_str, GRAPHICS,
            TYPE_SETTINGS, NULL, sfFalse, NULL, NULL}, wolf->data->font,
        &(sfVector2f){window->width / 2.0f, y},
        &(sfVector2f){1.1f, 1.1f});
    center_text_on_screen(text, window, y);
    if (text)
        push_front(&wolf->list[SETTINGS][TEXT], text);
    free(brightness_str);
}

static void init_max_fps(wolf_t *wolf, window_t *window, int max_fps, int y)
{
    char *max_fps_str = my_nbr_to_str(max_fps);
    text_t data = {"max_fps_value", max_fps_str, GRAPHICS,
        TYPE_SETTINGS, NULL, sfFalse, NULL, NULL};

    if (!max_fps_str)
        return;
    (void)window;
    init_graphics_value(wolf, &data, y, sfTrue);
    free(max_fps_str);
}

void init_graphics_params(settings_game_t *settings, wolf_t *wolf)
{
    init_resolution(wolf, wolf->window_data, &settings->resolution,
        wolf->window_data->height / 2.9f);
    init_fullscreen(wolf, wolf->window_data, settings->fullscreen);
    init_vsync(wolf, wolf->window_data, settings->vsync);
    init_fov(wolf, wolf->window_data, settings->fov);
    init_brightness(wolf, wolf->window_data, settings->brightness);
    init_max_fps(wolf, wolf->window_data, settings->max_fps,
        wolf->window_data->height / 2.9f + 400);
}
