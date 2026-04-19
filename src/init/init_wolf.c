/*
** EPITECH PROJECT, 2026
** init
** File description:
** player
*/

#include "../../include/wolf3d.h"

void push_front(list_t **list, void *data)
{
    list_t *new_node = malloc(sizeof(list_t));

    if (!new_node || !data)
        return;
    new_node->data = data;
    new_node->next = *list;
    *list = new_node;
}

window_t *init_window_data(void)
{
    window_t *window = calloc(1, sizeof(window_t));

    if (!window)
        return NULL;
    window->window = sfRenderWindow_create((sfVideoMode)
        {1920, 1080, 32}, "Wolf3D", sfClose, NULL);
    window->width = 1920;
    window->height = 1080;
    return window;
}

data_t *init_wolf_data(void)
{
    data_t *data = calloc(1, sizeof(data_t));

    if (!data)
        return NULL;
    data->font = sfFont_createFromFile("assets/font.ttf");
    return data;
}

wolf_t *init_wolf(void)
{
    wolf_t *wolf = calloc(1, sizeof(wolf_t));

    if (!wolf)
        return NULL;
    wolf->state = MENU;
    wolf->player = calloc(1, sizeof(player_t));
    if (!wolf->player) {
        free(wolf);
        return NULL;
    }
    init_player(wolf->player);
    wolf->window_data = init_window_data();
    wolf->data = init_wolf_data();
    init_menu_entities(wolf, wolf->window_data);
    init_menu_text(wolf, wolf->window_data);
    wolf->game = init_game();
    return wolf;
}
