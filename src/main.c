/*
** EPITECH PROJECT, 2026
** main
** File description:
** main
*/

#include "../include/wolf3d.h"

int get_map_tile(int tile_x, int tile_y)
{
    static const int map_data[MAP_HEIGHT][MAP_WIDTH] = {
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1}
    };

    return map_data[tile_y][tile_x];
}

void check_event(sfRenderWindow *window, sfEvent event, wolf_t *wolf)
{
    sfVector2u scale = {0};

    if (event.type == sfEvtClosed || wolf->state == QUIT ||
        sfKeyboard_isKeyPressed(sfKeyEscape))
        sfRenderWindow_close(window);
    switch (wolf->state) {
        case MENU:
            manage_menu(wolf, event);
            break;
        case GAME:
            break;
        default:
            break;
    }
    if (event.type == sfEvtResized) {
        for (list_t *tmp = wolf->list[MENU][SPRITE]; tmp != NULL; tmp = tmp->next) {
            sfSprite_setPosition(tmp->data, (sfVector2f){scale.x / 2.f, scale.y / 2.f});
            sfSprite_setScale(tmp->data, (sfVector2f){1 * scale.x / 1920.f, 1 * scale.y / 1080.f});
        }
    }
}

static void stage(wolf_t *wolf, player_t *player, sfEvent event)
{
    move_player(wolf->player, event, wolf->game);
    sfRenderWindow_clear(wolf->window_data->window, sfBlack);
    draw_floor_and_ceiling(wolf->window_data);
    cast_all_rays(wolf->window_data, player, wolf->game->wall);
}

static void check_state(wolf_t *wolf, sfEvent event)
{
    switch (wolf->state) {
        case MENU:
            break;
        case GAME:
            stage(wolf, wolf->player, event);
            break;
        default:
            break;
    }
}

int program(sfRenderWindow *window, sfEvent event, wolf_t *wolf)
{
    while (sfRenderWindow_isOpen(window)) {
        sfRenderWindow_clear(window, sfBlack);
        while (sfRenderWindow_pollEvent(window, &event))
            check_event(window, event, wolf);
        check_state(wolf, event);
        draw_sprite_list(wolf);
        draw_text_list(wolf);
        sfRenderWindow_display(window);
    }
    free_wolf(wolf);
    return 0;
}

int main(void)
{
    wolf_t *wolf = init_wolf();
    sfEvent event;

    if (!wolf)
        return 84;
    return program(wolf->window_data->window, event, wolf);
}
