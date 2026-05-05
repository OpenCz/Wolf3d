/*
** EPITECH PROJECT, 2026
** menu
** File description:
** menu
*/

#include "../include/wolf3d.h"

static void free_game(game_t *game)
{
    sfClock_destroy(game->clock);
    free(game->wall->pixel);
    sfSprite_destroy(game->wall->sprite);
    sfTexture_destroy(game->wall->texture);
    free(game->wall);
    free(game->zbuffer);
    free(game);
}

static void free_rectangles(wolf_t *wolf, int state)
{
    rect_t *rect = NULL;
    list_t *next = NULL;

    for (list_t *curr = wolf->list[state][RECT]; curr; curr = next) {
        next = curr->next;
        rect = (rect_t *)curr->data;
        sfRectangleShape_destroy(rect->rect);
        sfTexture_destroy(rect->texture);
        free(rect);
        free(curr);
    }
}

static void free_texts(wolf_t *wolf, int state)
{
    text_t *text = NULL;
    list_t *next = NULL;

    for (list_t *curr = wolf->list[state][TEXT]; curr; curr = next) {
        next = curr->next;
        text = (text_t *)curr->data;
        sfText_destroy(text->text);
        free(text);
        free(curr);
    }
}

static void free_entities(wolf_t *wolf, int state)
{
    entity_t *entity = NULL;
    list_t *next = NULL;

    for (list_t *curr = wolf->list[state][SPRITE]; curr; curr = next) {
        next = curr->next;
        entity = (entity_t *)curr->data;
        sfSprite_destroy(entity->sprite);
        sfTexture_destroy(entity->texture);
        free(entity);
        free(curr);
    }
}

static void free_line(wolf_t *wolf, int state)
{
    rect_t *line = NULL;
    list_t *next = NULL;

    for (list_t *curr = wolf->list[state][LINE]; curr; curr = next) {
        next = curr->next;
        line = (rect_t *)curr->data;
        sfRectangleShape_destroy(line->rect);
        free(line);
        free(curr);
    }
}

static void free_settings(wolf_t *wolf)
{
    free_rectangles(wolf, SETTINGS);
    free_texts(wolf, SETTINGS);
    free_entities(wolf, SETTINGS);
    free_line(wolf, SETTINGS);
}

static void free_list(wolf_t *wolf)
{
    free_texts(wolf, MENU);
    free_entities(wolf, MENU);
}

static void free_window_data(window_t *window_data)
{
    if (window_data) {
        sfRenderWindow_destroy(window_data->window);
        free(window_data);
    }
}

void free_wolf(wolf_t *wolf)
{
    if (wolf->connected)
        client_close(&wolf->net);
    free_window_data(wolf->window_data);
    free(wolf->player);
    free_game(wolf->game);
    free_list(wolf);
    free_settings(wolf);
    free(wolf->data);
    free(wolf);
}
