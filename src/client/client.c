/*
** EPITECH PROJECT, 2026
** client
** File description:
** client
*/

#include "network.h"

int main(int argc, char **argv)
{
    const char *ip = argc > 1 ? argv[1] : "127.0.0.1";
    sfTcpSocket *socket = sfTcpSocket_create();

    if (sfTcpSocket_connect(socket, sfIpAddress_fromString(ip),
            4999, sfTime_Zero) == sfSocketDone)
        printf("Connecte au serveur !\n");
    else
        printf("Echec de la connexion.\n");
    while (1);
    sfTcpSocket_destroy(socket);
    return 0;
}
