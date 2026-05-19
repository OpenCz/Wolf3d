/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** Settings and UI functions
*/

#ifndef SETTINGS_H
    #define SETTINGS_H

    #include "types.h"

void settings(wolf_t *wolf);
void manage_settings(wolf_t *wolf, sfEvent event);
sfBool click_settings_triangle(wolf_t *wolf, sfEvent event);
void hover_settings_triangle(wolf_t *wolf, sfEvent event);
void apply_triangle_action(wolf_t *wolf, text_t *text, int direction);
void init_settings_entities(wolf_t *wolf, window_t *window);
void init_settings_buttons(wolf_t *wolf, window_t *window);
void init_audio(wolf_t *wolf, window_t *window);
void init_gameplay(wolf_t *wolf, window_t *window);
settings_game_t *init_settings_params(void);
void init_graphics_params(settings_game_t *settings, wolf_t *wolf);
void apply_settings(wolf_t *wolf);
void handle_window_recreate(wolf_t *wolf);
void reset_settings(wolf_t *wolf);
void update_ui_layout(wolf_t *wolf, int old_width, int old_height);
void create_setting_triangles(window_t *window, float y,
    triangle_t **triangles);
void push_double_arrow(wolf_t *wolf, triangle_t **triangles);

#endif
