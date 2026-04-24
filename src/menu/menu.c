/*
** EPITECH PROJECT, 2026
** menu
** File description:
** menu
*/

#include "../../include/wolf3d.h"

static void move_cloud(wolf_t *wolf)
{
    entity_t *cloud = get_entity(wolf->list[MENU][SPRITE], "cloud");
    sfVector2f pos;
    float dt = sfTime_asSeconds(sfClock_getElapsedTime(cloud->clock));

    sfClock_restart(cloud->clock);
    sfSprite_move(cloud->sprite, (sfVector2f){100 * dt, 0});
    pos = sfSprite_getPosition(cloud->sprite);
    if (pos.x > wolf->window_data->width)
        sfSprite_setPosition(cloud->sprite,
            (sfVector2f){0, wolf->window_data->height / 4});
}

void menu(wolf_t *wolf)
{
    move_cloud(wolf);
}
