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
    free(game->pixel);
    free(game->wall);
    free(game->zbuffer);
    sfSprite_destroy(game->sprite);
    sfTexture_destroy(game->texture);
    free(game);
}

static void free_list(wolf_t *wolf)
{
    text_t *text = NULL;
    entity_t *entity = NULL;
    list_t *next = NULL;

    for (list_t *curr = wolf->list[MENU][SPRITE]; curr; curr = next) {
        next = curr->next;
        entity = (entity_t *)curr->data;
        sfSprite_destroy(entity->sprite);
        sfTexture_destroy(entity->texture);
        free(entity);
        free(curr);
    }
    for (list_t *curr = wolf->list[MENU][TEXT]; curr; curr = next) {
        next = curr->next;
        text = (text_t *)curr->data;
        sfText_destroy(text->text);
        free(text);
        free(curr);
    }
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
    free(wolf->data);
    free(wolf);
}
