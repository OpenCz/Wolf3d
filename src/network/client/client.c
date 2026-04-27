/*
** EPITECH PROJECT, 2026
** network
** File description:
** client
*/

#include <stdio.h>
#include <string.h>
#include "network.h"

int client_init(client_t *client, const char *ip, int port)
{
    sfIpAddress address;
    sfTime timeout = sfMilliseconds(500);

    if (!client || !ip)
        return -1;
    address = sfIpAddress_fromString(ip);
    client->socket = sfTcpSocket_create();
    if (!client->socket)
        return -1;
    if (sfTcpSocket_connect(client->socket, address, port, timeout)
        != sfSocketDone) {
        sfTcpSocket_destroy(client->socket);
        client->socket = NULL;
        return -1;
    }
    sfTcpSocket_setBlocking(client->socket, sfFalse);
    snprintf(client->server_ip, sizeof(client->server_ip), "%s", ip);
    client->player_id = MAX_PLAYERS;
    return 0;
}

int client_send_packet(client_t *client, network_packet_t *packet)
{
    sfSocketStatus s;

    if (!client || !packet || !client->socket)
        return -1;
    packet->player_id = client->player_id;
    s = sfTcpSocket_send(client->socket, packet, sizeof(network_packet_t));
    if (s == sfSocketDone || s == sfSocketNotReady)
        return 0;
    return -1;
}

int client_recv_packet(client_t *client, network_packet_t *packet)
{
    size_t received;
    sfSocketStatus status;

    if (!client || !packet || !client->socket)
        return -1;
    status = sfTcpSocket_receive(client->socket, packet,
        sizeof(network_packet_t), &received);
    if (status == sfSocketNotReady)
        return 0;
    if (status == sfSocketDisconnected)
        return -1;
    if (status != sfSocketDone)
        return 0;
    return (int)received;
}

void client_close(client_t *client)
{
    if (!client || !client->socket)
        return;
    sfTcpSocket_disconnect(client->socket);
    sfTcpSocket_destroy(client->socket);
    client->socket = NULL;
}
