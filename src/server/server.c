/*
** EPITECH PROJECT, 2026
** server
** File description:
** server
*/

#include <SFML/Network.h>
#include <stdio.h>

int main(void)
{
    sfTcpListener *listener = sfTcpListener_create();
    sfTcpSocket *client = sfTcpSocket_create();

    sfTcpListener_listen(listener, 4999, sfIpAddress_Any);
    printf("Serveur en attente sur le port 4999...\n");
    if (sfTcpListener_accept(listener, &client) == sfSocketDone)
        printf("Client connecte !\n");
    while (1);
    sfTcpSocket_destroy(client);
    sfTcpListener_destroy(listener);
    return 0;
}
