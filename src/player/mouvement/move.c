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

static void move_forward(sfVector2f *new, player_t *p, wall_t *w, float dt)
{
    new->x = p->x + cosf(p->angle) * (get_speed(p, 100, 110) / TILE_SIZE) * dt;
    new->y = p->y + sinf(p->angle) * (get_speed(p, 100, 110) / TILE_SIZE) * dt;
    if (!check_collision(w, new->x, p->y))
        p->x = new->x;
    if (!check_collision(w, p->x, new->y))
        p->y = new->y;
}

static void move_backward(sfVector2f *new, player_t *p, wall_t *w, float dt)
{
    new->x = p->x - cosf(p->angle) * (100.0 / TILE_SIZE) * dt;
    new->y = p->y - sinf(p->angle) * (100.0 / TILE_SIZE) * dt;
    if (!check_collision(w, new->x, p->y))
        p->x = new->x;
    if (!check_collision(w, p->x, new->y))
        p->y = new->y;
}

static void move_forward_backward(wall_t *wall, player_t *p, float dt)
{
    float new_x = 0;
    float new_y = 0;

    if (sfKeyboard_isKeyPressed(sfKeyZ))
        move_forward(&(sfVector2f){new_x, new_y}, p, wall, dt);
    if (sfKeyboard_isKeyPressed(sfKeyS))
        move_backward(&(sfVector2f){new_x, new_y}, p, wall, dt);
}

static void move_left(sfVector2f *new, wall_t *wall, player_t *p, float dt)
{
    new->x = p->x + cosf(p->angle - M_PI / 2) * (get_speed(p, 60.0, 30) /
        TILE_SIZE) * dt;
    new->y = p->y + sinf(p->angle - M_PI / 2) * (get_speed(p, 60.0, 30) /
        TILE_SIZE) * dt;
    if (!check_collision(wall, new->x, p->y))
        p->x = new->x;
    if (!check_collision(wall, p->x, new->y))
        p->y = new->y;
}

static void move_right(sfVector2f *new, wall_t *wall, player_t *p, float dt)
{
    new->x = p->x + cosf(p->angle + M_PI / 2) * (get_speed(p, 60.0, 30) /
        TILE_SIZE) * dt;
    new->y = p->y + sinf(p->angle + M_PI / 2) * (get_speed(p, 60.0, 30) /
        TILE_SIZE) * dt;
    if (!check_collision(wall, new->x, p->y))
        p->x = new->x;
    if (!check_collision(wall, p->x, new->y))
        p->y = new->y;
}

static void move_side(wall_t *wall, player_t *p, float dt)
{
    float new_x = 0;
    float new_y = 0;

    if (sfKeyboard_isKeyPressed(sfKeyQ))
        move_left(&(sfVector2f){new_x, new_y}, wall, p, dt);
    if (sfKeyboard_isKeyPressed(sfKeyD)) {
        move_right(&(sfVector2f){new_x, new_y}, wall, p, dt);
    }
}

void move_player(player_t *player, sfEvent event, game_t *game)
{
    float dt =
        sfTime_asSeconds(sfClock_getElapsedTime(game->clock[MOVE_CLOCK]));

    (void)event;
    sfClock_restart(game->clock[MOVE_CLOCK]);
    move_side(game->wall, player, dt);
    move_forward_backward(game->wall, player, dt);
    manage_angle(player, dt);
}
