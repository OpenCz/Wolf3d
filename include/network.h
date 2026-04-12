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

typedef struct s_player_state {
    int id;
    float x;
    float y;
    float angle;
    int health;
} t_player_state;

typedef struct s_input_msg {
    int player_id;
    bool forward;
    bool backward;
    bool turn_left;
    bool turn_right;
    bool shoot;
} t_input_msg;

typedef struct s_world_state {
    t_player_state players[MAX_PLAYERS];
    int player_count;
    unsigned int tick;
} t_world_state;

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
