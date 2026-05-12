/*
** EPITECH PROJECT, 2026
** jump
** File description:
** jump
*/

#include "../../../include/wolf3d.h"

void on_ground(jump_t *jump)
{
    if (sfKeyboard_isKeyPressed(sfKeySpace)) {
        jump->jump_speed = 300.0f;
        jump->state = JUMPING;
    }
}

void jumping(player_t *p, jump_t *jump, float dt)
{
    jump->jump_speed -= 400.0f * dt;
    p->z += jump->jump_speed * dt;
    if (jump->jump_speed <= 0)
        jump->state = FALLING;
}

void falling(player_t *player, float dt)
{
    player->jump.jump_speed -= 400.0f * dt;
    player->z += player->jump.jump_speed * dt;
    if (player->z <= 0) {
        player->z = 0;
        player->jump.jump_speed = 0;
        player->jump.state = ON_GROUND;
    }
}

void jump_player(wolf_t *wolf, player_t *p)
{
    float dt = sfTime_asSeconds(sfClock_getElapsedTime(p->jump.clock));

    sfClock_restart(p->jump.clock);
    switch (p->jump.state) {
        case ON_GROUND:
            on_ground(&p->jump);
            break;
        case JUMPING:
            jumping(p, &p->jump, dt);
            break;
        case FALLING:
            falling(p, dt);
            break;
    }
}
