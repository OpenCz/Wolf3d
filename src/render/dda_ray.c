/*
** EPITECH PROJECT, 2026
** rays
** File description:
** rays
*/

#include "../../include/wolf3d.h"
#include <math.h>

static void init_ray(ray_t *ray, player_t *player, float dir_x, float dir_y)
{
    ray->map = (sfVector2i){(int)(player->x), (int)(player->y)};
    ray->delta_dist = (sfVector2f){fabsf(1.0f / dir_x), fabsf(1.0f / dir_y)};
    ray->side_dist = (sfVector2f){0, 0};
    ray->step = (sfVector2i){0, 0};
}

static void calculate_step(ray_t *ray, float ray_dir_x,
    float ray_dir_y, player_t *player)
{
    if (ray_dir_x < 0) {
        ray->step.x = -1;
        ray->side_dist.x = (player->x - ray->map.x) * ray->delta_dist.x;
    } else {
        ray->step.x = 1;
        ray->side_dist.x = (ray->map.x + 1.0f - player->x) * ray->delta_dist.x;
    }
    if (ray_dir_y < 0) {
        ray->step.y = -1;
        ray->side_dist.y = (player->y - ray->map.y) * ray->delta_dist.y;
    } else {
        ray->step.y = 1;
        ray->side_dist.y = (ray->map.y + 1.0f - player->y) * ray->delta_dist.y;
    }
}

float cast_ray(wall_t *wall, player_t *player,
    float dir_x, float dir_y)
{
    ray_t ray;
    int side = 0;

    init_ray(&ray, player, dir_x, dir_y);
    calculate_step(&ray, dir_x, dir_y, player);
    while (!is_wall(wall, ray.map.x, ray.map.y)) {
        if (ray.side_dist.x < ray.side_dist.y) {
            ray.side_dist.x += ray.delta_dist.x;
            ray.map.x += ray.step.x;
            side = 0;
        } else {
            ray.side_dist.y += ray.delta_dist.y;
            ray.map.y += ray.step.y;
            side = 1;
        }
    }
    return side == 0 ? ray.side_dist.x - ray.delta_dist.x :
        ray.side_dist.y - ray.delta_dist.y;
}
