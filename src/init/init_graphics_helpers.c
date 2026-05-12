/*
** EPITECH PROJECT, 2026
** ~/EpitechProjects/Wolf3d/src/init
** File description:
** init_graphics_helpers
*/

#include "wolf3d.h"

void center_text_on_screen(text_t *text, window_t *window, float y)
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

void create_setting_triangles(window_t *window, float y,
    triangle_t **triangles)
{
    triangles[0] = create_triangle(&(triangle_t){NULL, "left_res", GRAPHICS,
            TYPE_SETTINGS}, &(sfVector2f){window->width / 2.5f, y},
        (sfVector2f[3]){{-15, 0}, {0, 15}, {0, -15}});
    triangles[1] = create_triangle(&(triangle_t){NULL, "right_res", GRAPHICS,
            TYPE_SETTINGS}, &(sfVector2f){window->width * 0.6f, y},
        (sfVector2f[3]){{15, 0}, {0, 15}, {0, -15}});
}
