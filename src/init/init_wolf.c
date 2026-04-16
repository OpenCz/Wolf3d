/*
** EPITECH PROJECT, 2026
** init
** File description:
** player
*/

#include "../../include/wolf3d.h"

static void push_front(list_t **list, void *data)
{
    list_t *new_node = malloc(sizeof(list_t));

    if (!new_node || !data)
        return;
    new_node->data = data;
    new_node->next = *list;
    *list = new_node;
}

static entity_t *create_entity(const char *name,
    const char *texture_path, sfVector2f *pos, sfVector2f *scale)
{
    entity_t *entity = malloc(sizeof(entity_t));
    sfVector2u size;

    if (!entity)
        return NULL;
    entity->name = strdup(name);
    entity->texture = sfTexture_createFromFile(texture_path, NULL);
    if (!entity->name || !entity->texture) {
        if (entity->name)
            free(entity->name);
        free(entity);
        return NULL;
    }
    entity->sprite = sfSprite_create();
    sfSprite_setTexture(entity->sprite, entity->texture, sfTrue);
    size = sfTexture_getSize(entity->texture);
    sfSprite_setOrigin(entity->sprite, (sfVector2f){size.x / 2, size.y / 2});
    sfSprite_setPosition(entity->sprite, *pos);
    sfSprite_setScale(entity->sprite, *scale);
    return entity;
}

static void init_menu_entities(wolf_t *wolf, window_t *window)
{
    push_front(&wolf->list[MENU][SPRITE], create_entity("bar_main_menu",
            "assets/bar_main_menu.png",
            &(sfVector2f){window->width / 2, window->height / 1.06},
            &(sfVector2f){1.6, 1.22}));
    push_front(&wolf->list[MENU][SPRITE], create_entity("background",
            "assets/BG_main_menu.png",
            &(sfVector2f){window->width / 2, window->height / 2},
            &(sfVector2f){1.15, 1.21}));
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
    for (int i = 0; i < STATES; i++) {
        for (int j = 0; j < TO_DRAW; j++)
            wolf->list[i][j] = NULL;
    }
    wolf->window_data = init_window_data();
    init_menu_entities(wolf, wolf->window_data);
    return wolf;
}
