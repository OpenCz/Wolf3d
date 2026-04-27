/*
** EPITECH PROJECT, 2026
** network
** File description:
** server close
*/

#include "network.h"

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
