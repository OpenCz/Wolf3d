/*
** EPITECH PROJECT, 2026
** server
** File description:
** server
*/

#include "network.h"

static int init_listener(sfTcpListener **listener)
{
    *listener = sfTcpListener_create();
    if (*listener == NULL)
        return 84;
    if (sfTcpListener_listen(*listener, PORT_TCP,
            sfIpAddress_Any) != sfSocketDone) {
        sfTcpListener_destroy(*listener);
        return 84;
    }
    sfTcpListener_setBlocking(*listener, sfFalse);
    printf("Serveur en attente sur le port %d...\n", PORT_TCP);
    return 0;
}

static sfSocketStatus send_color_update(sfTcpSocket *socket,
    sfUint32 red, sfUint32 green, sfUint32 blue)
{
    sfPacket *packet = sfPacket_create();
    sfSocketStatus status;

    if (packet == NULL)
        return sfSocketError;
    sfPacket_writeUint32(packet, MSG_COLOR_UPDATE);
    sfPacket_writeUint32(packet, red);
    sfPacket_writeUint32(packet, green);
    sfPacket_writeUint32(packet, blue);
    status = sfTcpSocket_sendPacket(socket, packet);
    sfPacket_destroy(packet);
    return status;
}

static sfSocketStatus receive_color_update(sfTcpSocket *socket,
    sfUint32 *red, sfUint32 *green, sfUint32 *blue)
{
    sfPacket *packet = sfPacket_create();
    sfSocketStatus status;
    sfUint32 type = 0;

    if (packet == NULL)
        return sfSocketError;
    status = sfTcpSocket_receivePacket(socket, packet);
    if (status != sfSocketDone) {
        sfPacket_destroy(packet);
        return status;
    }
    type = sfPacket_readUint32(packet);
    if (!sfPacket_canRead(packet) || type != MSG_COLOR_UPDATE) {
        sfPacket_destroy(packet);
        return sfSocketError;
    }
    *red = sfPacket_readUint32(packet);
    if (!sfPacket_canRead(packet)) {
        sfPacket_destroy(packet);
        return sfSocketError;
    }
    *green = sfPacket_readUint32(packet);
    if (!sfPacket_canRead(packet)) {
        sfPacket_destroy(packet);
        return sfSocketError;
    }
    *blue = sfPacket_readUint32(packet);
    if (!sfPacket_canRead(packet)) {
        sfPacket_destroy(packet);
        return sfSocketError;
    }
    sfPacket_destroy(packet);
    return sfSocketDone;
}

static int find_free_slot(sfTcpSocket *clients[MAX_PLAYERS])
{
    for (int i = 0; i < MAX_PLAYERS; i++)
        if (clients[i] == NULL)
            return i;
    return -1;
}

static void remove_client(sfTcpSocket *clients[MAX_PLAYERS],
    sfSocketSelector *selector, int index, int *connected_players)
{
    if (index < 0 || index >= MAX_PLAYERS || clients[index] == NULL)
        return;
    sfSocketSelector_removeTcpSocket(selector, clients[index]);
    sfTcpSocket_disconnect(clients[index]);
    sfTcpSocket_destroy(clients[index]);
    clients[index] = NULL;
    if (*connected_players > 0)
        (*connected_players)--;
    printf("Client deconnecte (%d/%d).\n", *connected_players, MAX_PLAYERS);
}

static void destroy_clients(sfTcpSocket *clients[MAX_PLAYERS])
{
    for (int i = 0; i < MAX_PLAYERS; i++)
        if (clients[i] != NULL)
            sfTcpSocket_destroy(clients[i]);
}

static void accept_or_reject_client(sfTcpListener *listener,
    sfSocketSelector *selector, sfTcpSocket *clients[MAX_PLAYERS],
    int *connected_players)
{
    sfTcpSocket *new_client = sfTcpSocket_create();
    int index;

    if (new_client == NULL)
        return;
    if (sfTcpListener_accept(listener, &new_client) != sfSocketDone) {
        sfTcpSocket_destroy(new_client);
        return;
    }
    index = find_free_slot(clients);
    if (*connected_players >= MAX_PLAYERS || index == -1) {
        printf("Connexion refusee: serveur plein (%d joueurs max).\n",
            MAX_PLAYERS);
        sfTcpSocket_disconnect(new_client);
        sfTcpSocket_destroy(new_client);
        return;
    }
    sfTcpSocket_setBlocking(new_client, sfFalse);
    clients[index] = new_client;
    sfSocketSelector_addTcpSocket(selector, new_client);
    (*connected_players)++;
    printf("Client connecte (%d/%d).\n", *connected_players, MAX_PLAYERS);
}

static void broadcast_color(sfTcpSocket *clients[MAX_PLAYERS],
    sfSocketSelector *selector, int *connected_players,
    sfUint32 red, sfUint32 green, sfUint32 blue)
{
    sfSocketStatus status;

    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (clients[i] == NULL)
            continue;
        status = send_color_update(clients[i], red, green, blue);
        if (status == sfSocketDisconnected || status == sfSocketError)
            remove_client(clients, selector, i, connected_players);
    }
}

static void handle_ready_clients(sfTcpSocket *clients[MAX_PLAYERS],
    sfSocketSelector *selector, int *connected_players)
{
    sfSocketStatus status;
    sfUint32 red;
    sfUint32 green;
    sfUint32 blue;

    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (clients[i] == NULL ||
            !sfSocketSelector_isTcpSocketReady(selector, clients[i]))
            continue;
        status = receive_color_update(clients[i], &red, &green, &blue);
        if (status == sfSocketDone) {
            broadcast_color(clients, selector, connected_players,
                red, green, blue);
            continue;
        }
        if (status == sfSocketDisconnected || status == sfSocketError)
            remove_client(clients, selector, i, connected_players);
    }
}

static void run_server_loop(sfTcpListener *listener,
    sfTcpSocket *clients[MAX_PLAYERS])
{
    sfSocketSelector *selector = sfSocketSelector_create();
    int connected_players = 0;

    if (selector == NULL)
        return;
    sfSocketSelector_addTcpListener(selector, listener);
    while (1) {
        if (!sfSocketSelector_wait(selector, sfMilliseconds(100)))
            continue;
        if (sfSocketSelector_isTcpListenerReady(selector, listener))
            accept_or_reject_client(listener, selector,
                clients, &connected_players);
        handle_ready_clients(clients, selector, &connected_players);
    }
    sfSocketSelector_destroy(selector);
}

int main(void)
{
    sfTcpListener *listener = NULL;
    sfTcpSocket *clients[MAX_PLAYERS] = {NULL};

    if (init_listener(&listener) != 0)
        return 84;
    run_server_loop(listener, clients);
    destroy_clients(clients);
    sfTcpListener_destroy(listener);
    return 0;
}
