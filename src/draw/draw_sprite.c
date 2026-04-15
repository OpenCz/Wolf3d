/*
** EPITECH PROJECT, 2026
** draw
** File description:
** decor
*/

#include "../../include/wolf3d.h"

void resize_sprite_based_on_window(entity_t *entity)
{
    sfVector2u texture_size = sfTexture_getSize(entity->texture);
    float scale_x = (float)WINDOW_WIDTH / texture_size.x;
    float scale_y = (float)WINDOW_HEIGHT / texture_size.y;

    sfSprite_setScale(entity->sprite, (sfVector2f){scale_x, scale_y});
}

void draw_sprite_list(wolf_t *wolf, sfRenderWindow *window)
{
    entity_t *entity = NULL;

    for (list_t *c = wolf->list[wolf->state][SPRITE]; c; c = c->next) {
        entity = (entity_t *)c->data;
        sfRenderWindow_drawSprite(window, entity->sprite, NULL);
    }
}
