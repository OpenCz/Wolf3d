/*
** EPITECH PROJECT, 2026
** net
** File description:
** net
*/

#include <SFML/Network.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef NET_H
    #define NET_H

    #define PORT_TCP 4999
    #define PORT_UDP 5000

    #define MAX_PLAYERS 4
    #define TICK_RATE 20

typedef struct player_state_s {
    int id;
    float x;
    float y;
    float angle;
    int health;
} player_state_t;

typedef struct input_msg_s {
    int player_id;
    bool forward;
    bool backward;
    bool turn_left;
    bool turn_right;
    bool shoot;
} input_msg_t;

typedef struct world_state_s {
    player_state_t players[MAX_PLAYERS];
    int player_count;
    unsigned int tick;
} world_state_t;

typedef enum {
    MSG_PLAYER_JOIN,
    MSG_PLAYER_QUIT,
    MSG_PLAYER_MOVE,
    MSG_PLAYER_SHOOT,
    MSG_PLAYER_DEATH,
    MSG_PLAYER_INPUT,
    MSG_COLOR_UPDATE,
    MSG_WORLD_STATE
} net_status_t;

#endif
