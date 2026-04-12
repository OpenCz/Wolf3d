/*
** EPITECH PROJECT, 2026
** net
** File description:
** net
*/

#include <SFML/Network.h>
#include <stdio.h>

#ifndef NET_H
    #define NET_H

    #define PORT_TCP 4999
    #define PORT_UDP 5000

    #define MAX_PLAYERS 4
    #define TICK_RATE 20

typedef enum {
    MSG_PLAYER_JOIN,
    MDG_PLAYER_QUIT,
    MSG_PLAYER_MOVE,
    MSG_PLAYER_SHOOT,
    MSG_PLAYER_DEATH,
    MSG_PLAYER_INPUT,
    MSG_WOLRD_STATE
} net_status_t;

#endif
