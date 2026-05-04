/*
** EPITECH PROJECT, 2026
** main
** File description:
** main
*/

#include "../include/wolf3d.h"
#include <time.h>

static const char *const SERVER_IP = "10.73.190.141";

int get_map_tile(int tile_x, int tile_y)
{
    static const int map_data[MAP_HEIGHT][MAP_WIDTH] = {
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 2, 0, 0, 0, 1},
        {1, 0, 0, 2, 0, 2, 0, 1},
        {1, 0, 0, 0, 0, 2, 0, 1},
        {1, 0, 2, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1}
    };

    return map_data[tile_y][tile_x];
}

void check_event(sfRenderWindow *window, sfEvent event, wolf_t *wolf)
{
    if (event.type == sfEvtClosed || wolf->state == QUIT ||
        sfKeyboard_isKeyPressed(sfKeyEscape))
        sfRenderWindow_close(window);
    switch (wolf->state) {
        case MENU:
            manage_menu(wolf, event);
            break;
        case GAME:
            break;
        case SETTINGS:
            manage_settings(wolf, event);
            break;
        default:
            break;
    }
}

static void handle_recv_packet(wolf_t *wolf, network_packet_t *pkt)
{
    if (pkt->type != PKT_CONNECT)
        return;
    if (wolf->net.player_id == MAX_PLAYERS) {
        wolf->net.player_id = pkt->player_id;
        printf("[Network] Connected as player %u\n", pkt->player_id);
        if (pkt->player_id != 1)
            return;
        wolf->player->x = TILE_SIZE * 5.5f;
        wolf->player->y = TILE_SIZE * 1.5f;
        return;
    }
    if (pkt->player_id != wolf->net.player_id)
        printf("[Network] Player %u joined the game\n", pkt->player_id);
}

static void handle_recv_position(wolf_t *wolf, network_packet_t *pkt)
{
    if (pkt->type != PKT_PLAYER_POS)
        return;
    if (pkt->player_id == wolf->net.player_id || pkt->player_id >= MAX_PLAYERS)
        return;
    wolf->others[pkt->player_id].x = pkt->x;
    wolf->others[pkt->player_id].y = pkt->y;
    wolf->others[pkt->player_id].angle = pkt->angle;
    if ((int)pkt->player_id >= wolf->nb_others)
        wolf->nb_others = (int)pkt->player_id + 1;
}

static void network_send(wolf_t *wolf, sfClock *send_clock)
{
    network_packet_t pkt;

    if (sfTime_asSeconds(sfClock_getElapsedTime(send_clock)) < 0.05f)
        return;
    sfClock_restart(send_clock);
    memset(&pkt, 0, sizeof(pkt));
    pkt.type = PKT_PLAYER_POS;
    pkt.x = wolf->player->x;
    pkt.y = wolf->player->y;
    pkt.angle = wolf->player->angle;
    if (client_send_packet(&wolf->net, &pkt) < 0)
        wolf->connected = 0;
}

static void network_update(wolf_t *wolf, sfClock *send_clock)
{
    network_packet_t pkt;

    if (!wolf->connected)
        return;
    while (client_recv_packet(&wolf->net, &pkt) > 0) {
        handle_recv_packet(wolf, &pkt);
        handle_recv_position(wolf, &pkt);
    }
    if (wolf->state == GAME && wolf->net.player_id != MAX_PLAYERS)
        network_send(wolf, send_clock);
}

static void stage(wolf_t *wolf, player_t *player, sfEvent event)
{
    move_player(wolf->player, event, wolf->game);
    is_near_monster(wolf, player);
    check_player_state(wolf);
    sfRenderWindow_clear(wolf->window_data->window, sfBlack);
    draw_floor_and_ceiling(wolf->window_data);
    cast_all_rays(wolf->window_data, player, wolf->game);
    draw_other_players(wolf);
    render_pixels(wolf->game, wolf->window_data);
}

static void check_state(wolf_t *wolf, sfEvent event)
{
    switch (wolf->state) {
        case MENU:
            menu(wolf);
            break;
        case GAME:
            stage(wolf, wolf->player, event);
            break;
        case SETTINGS:
            settings(wolf);
            break;
        default:
            break;
    }
}

int program(sfRenderWindow *window, sfEvent event, wolf_t *wolf)
{
    sfClock *send_clock = sfClock_create();

    if (!send_clock)
        return 84;
    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_display(window);
    printf("[Network] Connecting to %s:%d...\n", SERVER_IP, PORT);
    wolf->connected = client_init(&wolf->net, SERVER_IP, PORT) == 0;
    if (!wolf->connected)
        printf("[Network] Connection failed to %s:%d\n", SERVER_IP, PORT);
    while (sfRenderWindow_isOpen(window)) {
        sfRenderWindow_clear(window, sfBlack);
        while (sfRenderWindow_pollEvent(window, &event))
            check_event(window, event, wolf);
        network_update(wolf, send_clock);
        check_state(wolf, event);
        draw_sprite_list(wolf);
        draw_text_list(wolf);
        sfRenderWindow_display(window);
    }
    sfClock_destroy(send_clock);
    free_wolf(wolf);
    return 0;
}

int main(void)
{
    wolf_t *wolf = init_wolf();

    if (!wolf)
        return 84;
    return program(wolf->window_data->window, (sfEvent){0}, wolf);
}
