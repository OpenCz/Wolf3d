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

window_t *init_window_data(void)
{
    window_t *window = malloc(sizeof(window_t));

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
    data_t *data = malloc(sizeof(data_t));

    if (!data)
        return NULL;
    data->font = sfFont_createFromFile("assets/font.ttf");
    return data;
}

static int init_wolf_player_data(wolf_t *wolf)
{
    wolf->window_data = init_window_data();
    wolf->data = init_wolf_data();
    wolf->player = init_player(wolf->window_data, PLAYER);
    if (!wolf->player || !wolf->window_data || !wolf->data)
        return -1;
    return 0;
}

static sfRectangleShape *set_slot_position(sfVector2f *size,
    sfVector2f *pos, sfColor *color)
{
    sfRectangleShape *rect = sfRectangleShape_create();

    sfRectangleShape_setSize(rect, *size);
    sfRectangleShape_setOrigin(rect,
        (sfVector2f){size->x / 2, size->y / 2});
    sfRectangleShape_setFillColor(rect, *color);
    sfRectangleShape_setOutlineThickness(rect, 3);
    sfRectangleShape_setOutlineColor(rect, sfBlack);
    sfRectangleShape_setPosition(rect, *pos);
    return rect;
}

static window_t *create_inv(window_t *win, inv_t *inv)
{
    sfVector2f size = {win->width / 2.5, win->height / 3};
    sfVector2f slot = {win->width / 12, win->height / 12};
    float space = 20;
    float x = win->width / 2 - ((slot.x * 4) + (space * 3)) / 2 + slot.x / 2;
    float y = win->height / 2 - ((slot.y * 2) + space) / 2 + slot.y / 2;

    inv->open = sfFalse;
    inv->rect[0] = set_slot_position(&size,
        &(sfVector2f){win->width / 2, win->height / 2},
        &(sfColor){110, 67, 32, 255});
    for (int i = 0; i < 8; i++) {
        size = (sfVector2f){x + i % 4 * (slot.x + space),
            y + i / 4 * (slot.y + space)};
        inv->rect[i + 1] = set_slot_position(&slot, &size, &sfWhite);
    }
    inv->rect[9] = set_slot_position(&(sfVector2f){win->width, win->height},
        &(sfVector2f){win->width / 2, win->height / 2},
        &(sfColor){120, 120, 120, 150});
    return win;
}

static int init_wolf_game_data(wolf_t *wolf)
{
    init_menu_entities(wolf, wolf->window_data);
    init_menu_text(wolf, wolf->window_data);
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

wolf_t *init_wolf(void)
{
    wolf_t *wolf = calloc(1, sizeof(wolf_t));

    if (!wolf)
        return NULL;
    if (init_wolf_player_data(wolf) < 0)
        return NULL;
    wolf->state = MENU;
    if (init_wolf_game_data(wolf) < 0 ||
        !create_inv(wolf->window_data, &wolf->game->inv))
        return NULL;
    push_front(&wolf->list[GAME][MONSTER],
        init_player(wolf->window_data, ENNEMY));
    return wolf;
}
