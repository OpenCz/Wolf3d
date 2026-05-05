/*
** EPITECH PROJECT, 2026
** ~/Epitech/Project/Wolf3d/src/settings
** File description:
** manage_settings
*/

#include "wolf3d.h"

static void center_text_on_rect(sfText *text, sfRectangleShape *rect)
{
    sfFloatRect text_bounds = sfText_getLocalBounds(text);
    sfFloatRect rect_bounds = sfRectangleShape_getGlobalBounds(rect);

    sfText_setOrigin(text, (sfVector2f) {
            text_bounds.left + text_bounds.width / 2.0f,
            text_bounds.top + text_bounds.height / 2.0f});
    sfText_setPosition(text, (sfVector2f) {
            rect_bounds.left + rect_bounds.width / 2.0f,
            rect_bounds.top + rect_bounds.height / 2.0f});
}

static void create_settings_action(wolf_t *wolf, float x, float y,
    text_t *info)
{
    sfVector2f pos;
    sfVector2f size;
    rect_t *rect;
    text_t *text;

    pos = (sfVector2f){x, y};
    size = (sfVector2f){380.0f, 70.0f};
    rect = create_rectangles(&(rect_t){(char *)info->name, info->state, NULL,
            NULL, NULL,
            TYPE_SETTINGS}, "assets/settings_button.png", &pos, &size);
    text = create_text(&(text_t){(char *)info->name, (char *)info->content,
            info->state, TYPE_SETTINGS, NULL},
        wolf->data->font, &pos, &(sfVector2f){1.0f, 1.0f});
    if (!rect || !text)
        return;
    sfText_setCharacterSize(text->text, 28);
    center_text_on_rect(text->text, rect->rect);
    push_front(&wolf->list[SETTINGS][RECT], rect);
    push_front(&wolf->list[SETTINGS][TEXT], text);
}

static void create_settings_button(wolf_t *wolf, float x, float y,
    text_t *info)
{
    sfVector2f pos;
    sfVector2f size;
    rect_t *rect;
    text_t *text;

    pos = (sfVector2f){x, y};
    size = (sfVector2f){280.0f, 70.0f};
    rect = create_rectangles(&(rect_t){(char *)info->name, info->state, NULL,
            NULL, NULL,
            TYPE_SETTINGS}, "assets/settings_button_click.png", &pos, &size);
    text = create_text(&(text_t){(char *)info->name, (char *)info->content,
            info->state, TYPE_SETTINGS, NULL},
        wolf->data->font, &pos, &(sfVector2f){1.0f, 1.0f});
    if (!rect || !text)
        return;
    sfText_setCharacterSize(text->text, 28);
    center_text_on_rect(text->text, rect->rect);
    push_front(&wolf->list[SETTINGS][RECT], rect);
    push_front(&wolf->list[SETTINGS][TEXT], text);
}

void init_settings_buttons(wolf_t *wolf, window_t *window)
{
    float start_x = (window->width - (5 * 300.0f)) / 2.0f + 300.0f / 2.0f;
    float y = window->height / 4.8f;
    float second_y = window->height / 1.25f;
    char *names[] = {"graphics", "audio", "gameplay", "controls",
        "accessibility", "reset", "back", "apply"};
    char *contents[] = {"GRAPHICS", "AUDIO", "GAMEPLAY", "CONTROLS",
        "ACCESSIBILITY" , "RESET TO DEFAULT", "BACK", "APPLY"};
    int states[] = {GRAPHICS, AUDIO, GAMEPLAY, CONTROLS, ACCESSIBILITY};
    int i;
    text_t infos[] = {
        {names[0], contents[0], states[0], TYPE_SETTINGS, NULL},
        {names[1], contents[1], states[1], TYPE_SETTINGS, NULL},
        {names[2], contents[2], states[2], TYPE_SETTINGS, NULL},
        {names[3], contents[3], states[3], TYPE_SETTINGS, NULL},
        {names[4], contents[4], states[4], TYPE_SETTINGS, NULL},
        {names[5], contents[5], -1, TYPE_SETTINGS, NULL},
        {names[6], contents[6], -1, TYPE_SETTINGS, NULL},
        {names[7], contents[7], -1, TYPE_SETTINGS, NULL}
    };

    for (i = 0; i < 8; i++) {
        if (i < 5)
            create_settings_button(wolf, start_x + i * 300.0f, y, &infos[i]);
        else
            create_settings_action(wolf, start_x + 150.0f + (i - 5) * 450.0f, second_y, &infos[i]);
    }
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
            if (in_list_top(rect->name) == 0)
                wolf->settings_state = rect->state;
            if (in_list_bottom(rect->name) == 0)
                if (strcmp(rect->name, "back") == 0)
                    wolf->state = MENU;
            break;
        }
    }
}

static void hover_button(wolf_t *wolf, sfEvent event)
{
    rect_t *rect = NULL;
    sfFloatRect bounds;
    int hovered = 0;

    for (list_t *c = wolf->list[SETTINGS][RECT]; c; c = c->next) {
        rect = (rect_t *)c->data;
        bounds = sfRectangleShape_getGlobalBounds(rect->rect);
        if (sfFloatRect_contains(&bounds, event.mouseMove.x,
                event.mouseMove.y) && wolf->settings_state != rect->state) {
            sfRectangleShape_setFillColor(rect->rect, sfColor_fromRGBA(255, 255, 255, 125));
            hovered = 1;
        } else {
            sfRectangleShape_setFillColor(rect->rect, sfColor_fromRGBA(255, 255, 255, 255));
        }
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
        && event.mouseButton.button == sfMouseLeft)
        click_button(wolf, event);
    if (event.type == sfEvtMouseMoved)
        hover_button(wolf, event);
}
