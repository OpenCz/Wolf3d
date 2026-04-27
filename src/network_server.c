/*
** EPITECH PROJECT, 2026
** network
** File description:
** standalone server
*/

#include <signal.h>
#include <string.h>
#include <time.h>
#include "../include/network.h"

static int should_stop(void)
{
    sigset_t pending;

    if (sigpending(&pending) != 0)
        return 0;
    return sigismember(&pending, SIGINT);
}

static void block_sigint(void)
{
    sigset_t set;

    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigprocmask(SIG_BLOCK, &set, NULL);
}

static void handle_new_connection(server_t *server)
{
    network_packet_t pkt;
    int slot;

    slot = server_accept_client(server);
    if (slot < 0)
        return;
    memset(&pkt, 0, sizeof(pkt));
    pkt.type = PKT_CONNECT;
    pkt.player_id = slot;
    pkt.timestamp = time(NULL);
    server_send_to_client(server, slot, &pkt);
    server_broadcast_to_others(server, &pkt, slot);
}

static void handle_client_data(server_t *server, int i)
{
    network_packet_t pkt;

    if (server_recv_from_client(server, i, &pkt) > 0)
        server_broadcast_to_others(server, &pkt, i);
}

static void handle_ready_clients(server_t *server)
{
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (server->client_sockets[i] &&
            sfSocketSelector_isTcpSocketReady(server->selector,
                server->client_sockets[i]))
            handle_client_data(server, i);
    }
}

static void run_server_loop(server_t *server)
{
    sfTime timeout = sfMilliseconds(50);

    while (!should_stop()) {
        if (!sfSocketSelector_wait(server->selector, timeout))
            continue;
        if (sfSocketSelector_isTcpListenerReady(server->selector,
                server->listener))
            handle_new_connection(server);
        handle_ready_clients(server);
    }
}

int main(void)
{
    server_t server;

    block_sigint();
    if (server_init(&server, PORT) < 0)
        return 1;
    run_server_loop(&server);
    server_close(&server);
    return 0;
}
