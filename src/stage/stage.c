/*
** EPITECH PROJECT, 2026
** stage
** File description:
** stage
*/

#include "../include/wolf3d.h"
#include <time.h>

void stage(wolf_t *wolf, player_t *player, sfEvent event)
{
    if (!wolf->game->inv.open) {
        sprint_player(player);
        move_player(wolf->player, event, wolf->game);
        use_weapon(wolf->game, player->weapon);
    }
    is_near_monster(wolf, player);
    check_player_state(wolf);
    cast_all_rays(wolf, wolf->window_data, player, wolf->game);
    draw_other_entities(wolf, player);
    render_pixels(wolf->game, wolf->window_data);
    draw_weapon(wolf, wolf->window_data, player->weapon);
    if (!wolf->game->inv.open)
        draw_crosshair(wolf, wolf->window_data);
}
