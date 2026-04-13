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
    printf("Serveur en attente sur le port %d...\n", PORT_TCP);
    return 0;
}

static void destroy_clients(sfTcpSocket *clients[MAX_PLAYERS])
{
    for (int i = 0; i < MAX_PLAYERS; i++)
        if (clients[i] != NULL)
            sfTcpSocket_destroy(clients[i]);
}

static void store_or_reject_client(sfTcpSocket *clients[MAX_PLAYERS],
    int *connected_players, sfTcpSocket *new_client)
{
    if (*connected_players >= MAX_PLAYERS) {
        printf("Connexion refusee: serveur plein (%d joueurs max).\n",
            MAX_PLAYERS);
        sfTcpSocket_disconnect(new_client);
        sfTcpSocket_destroy(new_client);
        return;
    }
    clients[*connected_players] = new_client;
    (*connected_players)++;
    printf("Client connecte (%d/%d).\n", *connected_players, MAX_PLAYERS);
}

static void accept_client_loop(sfTcpListener *listener,
    sfTcpSocket *clients[MAX_PLAYERS])
{
    sfTcpSocket *new_client = NULL;
    int connected_players = 0;

    while (1) {
        new_client = sfTcpSocket_create();
        if (new_client == NULL)
            continue;
        if (sfTcpListener_accept(listener, &new_client) != sfSocketDone) {
            sfTcpSocket_destroy(new_client);
            continue;
        }
        store_or_reject_client(clients, &connected_players, new_client);
    }
}

int main(void)
{
    sfTcpListener *listener = NULL;
    sfTcpSocket *clients[MAX_PLAYERS] = {NULL};

    if (init_listener(&listener) != 0)
        return 84;
    accept_client_loop(listener, clients);
    destroy_clients(clients);
    sfTcpListener_destroy(listener);
    return 0;
}
