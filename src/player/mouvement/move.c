/*
** EPITECH PROJECT, 2026
** main
** File description:
** main
*/

#include "../../../include/wolf3d.h"

static void manage_angle(player_t *player, float dt)
{
    float rotation_speed = 2.0f;

    if (sfKeyboard_isKeyPressed(sfKeyRight))
        player->angle += rotation_speed * dt;
    if (sfKeyboard_isKeyPressed(sfKeyLeft))
        player->angle -= rotation_speed * dt;
}

static int check_collision(wall_t *wall, float x, float y)
{
    float min = WALL_MIN_DISTANCE;

    return is_wall(wall, (int)((x - min)), (int)((y - min))) ||
        is_wall(wall, (int)((x + min)), (int)((y - min))) ||
        is_wall(wall, (int)((x - min)), (int)((y + min))) ||
        is_wall(wall, (int)((x + min)), (int)((y + min)));
}

static void move_forward_backward(wall_t *wall, player_t *player, float dt)
{
    float new_x = 0;
    float new_y = 0;

    if (sfKeyboard_isKeyPressed(sfKeyZ)) {
        new_x = player->x + cosf(player->angle) * (100.0 / TILE_SIZE) * dt;
        new_y = player->y + sinf(player->angle) * (100.0 / TILE_SIZE) * dt;
        if (!check_collision(wall, new_x, player->y))
            player->x = new_x;
        if (!check_collision(wall, player->x, new_y))
            player->y = new_y;
    }
    if (sfKeyboard_isKeyPressed(sfKeyS)) {
        new_x = player->x - cosf(player->angle) * (100.0 / TILE_SIZE) * dt;
        new_y = player->y - sinf(player->angle) * (100.0 / TILE_SIZE) * dt;
        if (!check_collision(wall, new_x, player->y))
            player->x = new_x;
        if (!check_collision(wall, player->x, new_y))
            player->y = new_y;
    }
}

static void move_side(wall_t *wall, player_t *p, float dt)
{
    float new_x = 0;
    float new_y = 0;

    if (sfKeyboard_isKeyPressed(sfKeyQ)) {
        new_x = p->x + cosf(p->angle - M_PI / 2) * (60.0 / TILE_SIZE) * dt;
        new_y = p->y + sinf(p->angle - M_PI / 2) *
            (60.0 / TILE_SIZE) * dt;
        if (!check_collision(wall, new_x, p->y))
            p->x = new_x;
        if (!check_collision(wall, p->x, new_y))
            p->y = new_y;
    }
    if (sfKeyboard_isKeyPressed(sfKeyD)) {
        new_x = p->x + cosf(p->angle + M_PI / 2) * (60.0 / TILE_SIZE) * dt;
        new_y = p->y + sinf(p->angle + M_PI / 2) * (60.0 / TILE_SIZE) * dt;
        if (!check_collision(wall, new_x, p->y))
            p->x = new_x;
        if (!check_collision(wall, p->x, new_y))
            p->y = new_y;
    }
}

void move_player(player_t *player, sfEvent event, game_t *game)
{
    float dt = sfTime_asSeconds(sfClock_getElapsedTime(game->clock));

    (void)event;
    sfClock_restart(game->clock);
    move_forward_backward(game->wall, player, dt);
    move_side(game->wall, player, dt);
    manage_angle(player, dt);
}
