/*
** EPITECH PROJECT, 2026
** ~/Epitech/Project/Wolf3d/src/settings
** File description:
** settings triangle events
*/

#include "wolf3d.h"

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
