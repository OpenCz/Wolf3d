/*
** EPITECH PROJECT, 2026
** ~/Epitech/Project/Wolf3d/src/settings
** File description:
** manage_settings
*/

#include "wolf3d.h"

static int in_list_top(char *name)
{
    char *names[] = {"graphics", "audio", "gameplay", "controls",
        "accessibility"};

    for (int i = 0; i < 5; i++) {
        if (strcmp(name, names[i]) == 0)
            return 0;
    }
    return 84;
}

static void action_button(wolf_t *wolf, char *name, int state)
{
    if (in_list_top(name) == 0)
        wolf->settings_state = state;
    if (strcmp(name, "back") == 0)
        wolf->state = MENU;
    if (strcmp(name, "apply") == 0)
        apply_settings(wolf);
    if (strcmp(name, "reset") == 0)
        reset_settings(wolf);
}

static void click_button(wolf_t *wolf, sfEvent event)
{
    rect_t *rect = NULL;
    sfFloatRect bounds;

    for (list_t *c = wolf->list[SETTINGS][RECT]; c; c = c->next) {
        rect = (rect_t *)c->data;
        bounds = sfRectangleShape_getGlobalBounds(rect->rect);
        if (sfFloatRect_contains(&bounds, event.mouseButton.x,
                event.mouseButton.y)) {
            action_button(wolf, rect->name, rect->state);
            break;
        }
    }
}

static void hover_button(wolf_t *wolf, sfEvent event)
{
    rect_t *rect = NULL;
    sfFloatRect bounds;

    for (list_t *c = wolf->list[SETTINGS][RECT]; c; c = c->next) {
        rect = (rect_t *)c->data;
        bounds = sfRectangleShape_getGlobalBounds(rect->rect);
        if (sfFloatRect_contains(&bounds, event.mouseMove.x,
                event.mouseMove.y) && wolf->settings_state != rect->state)
            sfRectangleShape_setFillColor(rect->rect, sfColor_fromRGBA(255,
                    255, 255, 125));
        else
            sfRectangleShape_setFillColor(rect->rect, sfColor_fromRGBA(255,
                    255, 255, 255));
    }
}

void manage_settings(wolf_t *wolf, sfEvent event)
{
    if (iskeypressed(sfKeyEscape, event))
        wolf->state = MENU;
    if (iskeypressed(sfKeyRight, event) && wolf->settings_state < ACCESSIBILITY)
        wolf->settings_state++;
    if (iskeypressed(sfKeyLeft, event) && wolf->settings_state > GRAPHICS)
        wolf->settings_state--;
    if (event.type == sfEvtMouseButtonPressed
        && event.mouseButton.button == sfMouseLeft
        && click_settings_triangle(wolf, event) == sfFalse)
        click_button(wolf, event);
    if (event.type == sfEvtMouseMoved) {
        hover_button(wolf, event);
        hover_settings_triangle(wolf, event);
    }
}
