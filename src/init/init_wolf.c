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

void create_cursor(window_t *win, crosshair_t *ch)
{
    sfVector2f pos = {win->width / 2, win->height / 2};

    ch->cursor = create_entity("cursor", "assets/crosshair.png",
        &pos, &(sfVector2f){0.2, 0.2});
    ch->pos = pos;
}

window_t *init_window_data(wolf_t *wolf)
{
    window_t *window = malloc(sizeof(window_t));

    if (!window)
        return NULL;
    window->window = sfRenderWindow_create(wolf->settings->resolution,
        "Wolf3D", sfClose, NULL);
    window->width = wolf->settings->resolution.width;
    window->height = wolf->settings->resolution.height;
    return window;
}

data_t *init_wolf_data(void)
{
    data_t *data = malloc(sizeof(data_t));

    if (!data)
        return NULL;
    data->font = sfFont_createFromFile("assets/font.ttf");
    return data;
}

static int init_wolf_player_data(wolf_t *wolf)
{
    wolf->window_data = init_window_data(wolf);
    wolf->data = init_wolf_data();
    wolf->player = init_player(wolf->window_data, PLAYER);
    if (!wolf->player || !wolf->window_data || !wolf->data)
        return -1;
    return 0;
}

static void init_settings(wolf_t *wolf)
{
    init_settings_entities(wolf, wolf->window_data);
    init_settings_buttons(wolf, wolf->window_data);
    init_graphics(wolf, wolf->window_data);
    init_audio(wolf, wolf->window_data);
    init_gameplay(wolf, wolf->window_data);
    init_graphics_params(wolf->settings, wolf);
}

static int init_wolf_game_data(wolf_t *wolf)
{
    init_menu_entities(wolf, wolf->window_data);
    init_menu_text(wolf, wolf->window_data);
    init_settings(wolf);
    wolf->game = init_game(wolf->window_data);
    if (!wolf->game)
        return -1;
    create_cursor(wolf->window_data, &wolf->game->crosshair);
    wolf->game->wall->pixel = malloc(wolf->window_data->height *
        wolf->window_data->width * 4);
    wolf->game->zbuffer = malloc(wolf->window_data->width * sizeof(float));
    if (!wolf->game->wall->pixel || !wolf->game->zbuffer)
        return -1;
    return 0;
}

static void init_state(wolf_t *wolf)
{
    wolf->state = MENU;
    wolf->menu_state = NEWGAME;
    wolf->settings_state = GRAPHICS;
}

wolf_t *init_wolf(void)
{
    wolf_t *wolf = calloc(1, sizeof(wolf_t));

    if (!wolf)
        return NULL;
    memset(wolf->list, 0, sizeof(wolf->list));
    wolf->settings = init_settings_params();
    wolf->tmp_settings = init_settings_params();
    if (!wolf->settings || !wolf->tmp_settings) {
        free(wolf);
        return NULL;
    }
    init_state(wolf);
    if (init_wolf_player_data(wolf) < 0)
        return NULL;
    wolf->state = MENU;
    if (init_wolf_game_data(wolf) < 0)
        return NULL;
    push_front(&wolf->list[GAME][MONSTER],
        init_player(wolf->window_data, ENNEMY));
    return wolf;
}
