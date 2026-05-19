/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** UI elements creation and drawing functions
*/

#ifndef UI_H
    #define UI_H

    #include "types.h"

text_t *create_text(text_t *data,
    sfFont *font, sfVector2f *pos, sfVector2f *scale);
rect_t *create_rectangles(rect_t *data, const char *texture_path,
    sfVector2f *pos, sfVector2f *scale);
rect_t *create_line(rect_t *data, sfVector2f *pos, sfVector2f *scale);
triangle_t *create_triangle(triangle_t *data,
    sfVector2f *pos, sfVector2f points[3]);
void center_text_on_screen(text_t *text, window_t *window, float y);
void draw_rect_list(wolf_t *wolf);
void draw_line_list(wolf_t *wolf);
void draw_triangle_list(wolf_t *wolf);
void init_graphics(wolf_t *wolf, window_t *window);
void init_setting_value(wolf_t *wolf, text_t *data, float y, int state);
void init_setting_text_value(wolf_t *wolf, setting_entry_t *entry, int state);
void init_setting_number_value(wolf_t *wolf, setting_entry_t *entry, int state);

#endif
