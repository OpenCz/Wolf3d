/*
** EPITECH PROJECT, 2026
** init
** File description:
** player
*/

#include "../../include/wolf3d.h"

static entity_t *create_entity(char *name,
    const char *texture_path, sfVector2f *pos, sfVector2f *scale)
{
    entity_t *entity = malloc(sizeof(entity_t));
    sfVector2u size;

    if (!entity)
        return NULL;
    entity->name = name;
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

void init_menu_entities(wolf_t *wolf, window_t *window)
{
    for (int i = 0; i < STATES; i++) {
        for (int j = 0; j < TO_DRAW; j++)
            wolf->list[i][j] = NULL;
    }
    push_front(&wolf->list[MENU][SPRITE], create_entity("background",
            "assets/BG_main_menu.png",
            &(sfVector2f){window->width / 2.f, window->height / 2.f},
            &(sfVector2f){1 * window->width / 1920.f, 1 * window->height / 1080.f}));
}
