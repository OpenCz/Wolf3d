/*
** EPITECH PROJECT, 2026
** draw
** File description:
** decor
*/

#include "../../include/wolf3d.h"

void draw_sprite_list(wolf_t *wolf, sfRenderWindow *window)
{
    entity_t *entity = NULL;

    for (list_t *c = wolf->list[wolf->state][SPRITE]; c; c = c->next) {
        entity = (entity_t *)c->data;
        sfRenderWindow_drawSprite(window, entity->sprite, NULL);
    }
}
