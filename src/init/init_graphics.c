/*
** EPITECH PROJECT, 2026
** ~/EpitechProjects/Wolf3d/src/init
** File description:
** init_graphics
*/

#include "wolf3d.h"

static void center_text_on_screen(text_t *text, window_t *window, float y)
{
    sfFloatRect bounds;

    if (!text)
        return;
    bounds = sfText_getLocalBounds(text->text);
    sfText_setOrigin(text->text, (sfVector2f){bounds.left + bounds.width / 2.0f,
            bounds.top + bounds.height / 2.0f});
    sfText_setPosition(text->text, (sfVector2f){window->width / 2.0f, y});
    sfText_setColor(text->text, sfColor_fromRGB(247, 167, 3));
}

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

void init_resolution(wolf_t *wolf, window_t *window, sfVideoMode *mode, int y)
{
    char *full_resolution = get_resolution_string(mode);
    text_t *text;
    triangle_t *triangles[2] = {
        create_triangle(&(triangle_t){NULL, "left_res", GRAPHICS,
                TYPE_SETTINGS}, &(sfVector2f){window->width / 2.5f, y},
            (sfVector2f[3]){{-15, 0}, {0, 15}, {0, -15}}),
        create_triangle(&(triangle_t){NULL, "right_res", GRAPHICS,
                TYPE_SETTINGS}, &(sfVector2f){window->width * 0.6f, y},
            (sfVector2f[3]){{15, 0}, {0, 15}, {0, -15}})};

    if (!full_resolution)
        return;
    text = create_text(&(text_t){"resolution_value", full_resolution, GRAPHICS,
            TYPE_SETTINGS, NULL, sfFalse}, wolf->data->font,
        &(sfVector2f){window->width / 2.0f, y}, &(sfVector2f){1.1f, 1.1f});
    center_text_on_screen(text, window, y);
    if (text)
        push_front(&wolf->list[SETTINGS][TEXT], text);
    free(full_resolution);
    push_double_arrow(wolf, triangles);
}

static void init_fullscreen(wolf_t *wolf, window_t *window, int is_fullscreen)
{
    text_t *text = NULL;
    char *fullscreen_str = is_fullscreen ? "ON" : "OFF";
    float y = window->height / 2.9f + 80;
    triangle_t *triangles[2] = {
        create_triangle(&(triangle_t){NULL, "left_res", GRAPHICS,
                TYPE_SETTINGS}, &(sfVector2f){window->width / 2.5f, y},
            (sfVector2f[3]){{-15, 0}, {0, 15}, {0, -15}}),
        create_triangle(&(triangle_t){NULL, "right_res", GRAPHICS,
                TYPE_SETTINGS}, &(sfVector2f){window->width * 0.6f, y},
            (sfVector2f[3]){{15, 0}, {0, 15}, {0, -15}})};

    text = create_text(&(text_t){"fullscreen_value", fullscreen_str, GRAPHICS,
            TYPE_SETTINGS, NULL, sfFalse}, wolf->data->font,
        &(sfVector2f){window->width / 2.0f, y},
        &(sfVector2f){1.1f, 1.1f});
    center_text_on_screen(text, window, y);
    if (text)
        push_front(&wolf->list[SETTINGS][TEXT], text);
    push_double_arrow(wolf, triangles);
}

static void init_vsync(wolf_t *wolf, window_t *window, int is_vsync)
{
    text_t *text = NULL;
    char *vsync_str = is_vsync ? "ON" : "OFF";
    float y = window->height / 2.9f + 160;
    triangle_t *triangles[2] = {
        create_triangle(&(triangle_t){NULL, "left_res", GRAPHICS,
                TYPE_SETTINGS}, &(sfVector2f){window->width / 2.5f, y},
            (sfVector2f[3]){{-15, 0}, {0, 15}, {0, -15}}),
        create_triangle(&(triangle_t){NULL, "right_res", GRAPHICS,
                TYPE_SETTINGS}, &(sfVector2f){window->width * 0.6f, y},
            (sfVector2f[3]){{15, 0}, {0, 15}, {0, -15}})};

    text = create_text(&(text_t){"vsync_value", vsync_str, GRAPHICS,
            TYPE_SETTINGS, NULL, sfFalse}, wolf->data->font,
        &(sfVector2f){window->width / 2.0f, y},
        &(sfVector2f){1.1f, 1.1f});
    center_text_on_screen(text, window, y);
    if (text)
        push_front(&wolf->list[SETTINGS][TEXT], text);
    push_double_arrow(wolf, triangles);
}

static void init_fov(wolf_t *wolf, window_t *window, int fov)
{
    text_t *text = NULL;
    char *fov_str = my_nbr_to_str(fov);
    float y = window->height / 2.9f + 240;

    if (!fov_str)
        return;
    text = create_text(&(text_t){"fov_value", fov_str, GRAPHICS,
            TYPE_SETTINGS, NULL, sfFalse}, wolf->data->font,
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
            TYPE_SETTINGS, NULL, sfFalse}, wolf->data->font,
        &(sfVector2f){window->width / 2.0f, y},
        &(sfVector2f){1.1f, 1.1f});
    center_text_on_screen(text, window, y);
    if (text)
        push_front(&wolf->list[SETTINGS][TEXT], text);
    free(brightness_str);
}

static void init_max_fps(wolf_t *wolf, window_t *window, int max_fps, int y)
{
    text_t *text = NULL;
    char *max_fps_str = my_nbr_to_str(max_fps);
    triangle_t *triangles[2] = {
        create_triangle(&(triangle_t){NULL, "left_res", GRAPHICS,
                TYPE_SETTINGS}, &(sfVector2f){window->width / 2.5f, y},
            (sfVector2f[3]){{-15, 0}, {0, 15}, {0, -15}}),
        create_triangle(&(triangle_t){NULL, "right_res", GRAPHICS,
                TYPE_SETTINGS}, &(sfVector2f){window->width * 0.6f, y},
            (sfVector2f[3]){{15, 0}, {0, 15}, {0, -15}})};

    if (!max_fps_str)
        return;
    text = create_text(&(text_t){"max_fps_value", max_fps_str, GRAPHICS,
            TYPE_SETTINGS, NULL, sfFalse}, wolf->data->font,
        &(sfVector2f){window->width / 2.0f, y}, &(sfVector2f){1.1f, 1.1f});
    center_text_on_screen(text, window, y);
    if (text)
        push_front(&wolf->list[SETTINGS][TEXT], text);
    free(max_fps_str);
    push_double_arrow(wolf, triangles);
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
