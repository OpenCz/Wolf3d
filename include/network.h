/*
** EPITECH PROJECT, 2026
** net
** File description:
** net
*/

#ifndef NET_H
    #define NET_H

    #include <SFML/Network.h>
    #include <stdbool.h>
    #include <stdio.h>

    #define MAX_PLAYERS 4

typedef struct s_player_state {
    int     id;
    float   x;
    float   y;
    float   angle;
    int     health;
} t_player_state;

typedef struct s_input_msg {
    int     player_id;
    bool    forward;
    bool    backward;
    bool    turn_left;
    bool    turn_right;
    bool    shoot;
} t_input_msg;

typedef struct s_world_state {
    t_player_state  players[MAX_PLAYERS];
    int             player_count;
    unsigned int    tick;
} t_world_state;

#endif
