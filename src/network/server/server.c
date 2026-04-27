/*
** EPITECH PROJECT, 2026
** network
** File description:
** server
*/

#include <string.h>
#include "network.h"

int server_init(server_t *server, int port)
{
    if (!server)
        return -1;
    server->listener = sfTcpListener_create();
    if (!server->listener)
        return -1;
    if (sfTcpListener_listen(server->listener, port, sfIpAddress_Any)
            != sfSocketDone) {
        sfTcpListener_destroy(server->listener);
        return -1;
    }
    server->selector = sfSocketSelector_create();
    sfSocketSelector_addTcpListener(server->selector, server->listener);
    server->nb_players = 0;
    memset(server->client_sockets, 0, sizeof(server->client_sockets));
    return 0;
}

int server_accept_client(server_t *server)
{
    sfTcpSocket *client = NULL;
    int slot;

    if (!server || server->nb_players >= MAX_PLAYERS)
        return -1;
    if (sfTcpListener_accept(server->listener, &client) != sfSocketDone) {
        if (client)
            sfTcpSocket_destroy(client);
        return -1;
    }
    slot = server->nb_players;
    sfTcpSocket_setBlocking(client, sfTrue);
    server->client_sockets[slot] = client;
    sfSocketSelector_addTcpSocket(server->selector, client);
    server->nb_players++;
    return slot;
}

int server_recv_from_client(server_t *server, int idx, network_packet_t *pkt)
{
    size_t received;
    sfSocketStatus status;

    if (!server || !pkt || !server->client_sockets[idx])
        return -1;
    status = sfTcpSocket_receive(server->client_sockets[idx], pkt,
        sizeof(*pkt), &received);
    if (status == sfSocketDisconnected || status == sfSocketError) {
        sfSocketSelector_removeTcpSocket(server->selector,
            server->client_sockets[idx]);
        sfTcpSocket_disconnect(server->client_sockets[idx]);
        sfTcpSocket_destroy(server->client_sockets[idx]);
        server->client_sockets[idx] = NULL;
        return -1;
    }
    return (int)received;
}

int server_send_to_client(server_t *server, int idx, network_packet_t *pkt)
{
    if (!server || !pkt || !server->client_sockets[idx])
        return -1;
    sfTcpSocket_send(server->client_sockets[idx], pkt, sizeof(*pkt));
    return 0;
}

int server_broadcast_to_others(server_t *server, network_packet_t *pkt,
    int sender)
{
    if (!server || !pkt)
        return -1;
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (i == sender || !server->client_sockets[i])
            continue;
        sfTcpSocket_send(server->client_sockets[i], pkt, sizeof(*pkt));
    }
    return 0;
}

void server_close(server_t *server)
{
    if (!server)
        return;
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (!server->client_sockets[i])
            continue;
        sfTcpSocket_disconnect(server->client_sockets[i]);
        sfTcpSocket_destroy(server->client_sockets[i]);
    }
    if (server->selector)
        sfSocketSelector_destroy(server->selector);
    if (server->listener)
        sfTcpListener_destroy(server->listener);
}
