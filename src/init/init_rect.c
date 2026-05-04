/*
** EPITECH PROJECT, 2026
** ~/Epitech/Project/Wolf3d/src/init
** File description:
** init_rectangle
*/

#include "wolf3d.h"

static rect_t *create_rectangles(rect_t *data, const char *texture_path,
    sfVector2f *pos, sfVector2f *scale)
{
    rect_t *rect = malloc(sizeof(rect_t));
    sfFloatRect rect_txt;

    if (!rect)
        return NULL;
    rect->rect = sfRectangleShape_create();
    rect->name = data->name;
    rect->state = data->state;
    rect->texture = sfTexture_createFromFile(texture_path, NULL);
    if (!rect->name || !rect->texture) {
        if (rect->name)
            free(rect->name);
        free(rect);
        return NULL;
    }
    sfRectangleShape_setSize(rect->rect, *scale);
        rect_txt = sfRectangleShape_getGlobalBounds(rect->rect);
        sfRectangleShape_setOrigin(rect->rect, (sfVector2f){rect_txt.width / 2,
            rect_txt.height / 2});
    sfRectangleShape_setPosition(rect->rect, *pos);
    sfRectangleShape_setTexture(rect->rect, rect->texture, sfTrue);
    return rect;
}

void init_settings_rect(wolf_t *wolf, window_t *window)
{
    float start_x = (window->width - (5 * 250)) / 1.85f;
    float y = window->height / 4.1f;

    const char *names[] = {"graphics", "audio", "gameplay", "controls", "accessibility"};
    int states[] = {GRAPHICS, AUDIO, GAMEPLAY, CONTROLS, ACCESSIBILITY};

    for (int i = 0; i < 5; i++) {
        push_front(&wolf->list[SETTINGS][RECT],
            create_rectangles(
                &(rect_t){names[i], states[i], NULL, NULL},
                "assets/settings_button.png",
                &(sfVector2f){start_x + i * 300, y},
                &(sfVector2f){280, 70}
            ));
    }
}
