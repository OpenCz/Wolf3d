/*
** EPITECH PROJECT, 2026
** network
** File description:
** network
*/

#ifndef NETWORK_H
    #define NETWORK_H
    #include <SFML/Network.h>
    #include <stdint.h>
    #include <stdlib.h>

    #define MAX_PLAYERS 4
    #define PORT 8080

typedef enum packet_type_e {
    PKT_CONNECT,
    PKT_DISCONNECT,
    PKT_PLAYER_POS,
    PKT_SHOOT,
    PKT_GAME_STATE,
} packet_type_t;

typedef struct network_packet_s {
    uint8_t type;
    uint32_t player_id;
    uint32_t timestamp;
    float x;
    float y;
    float angle;
    uint8_t data[512];
} network_packet_t;

typedef struct server_s {
    sfTcpListener *listener;
    sfTcpSocket *client_sockets[MAX_PLAYERS];
    sfSocketSelector *selector;
    int nb_players;
} server_t;

typedef struct client_s {
    sfTcpSocket *socket;
    uint32_t player_id;
    char server_ip[16];
} client_t;

int server_init(server_t *server, int port);
int server_accept_client(server_t *server);
int server_recv_from_client(server_t *server,
    int idx, network_packet_t *pkt);
int server_send_to_client(server_t *server,
    int idx, network_packet_t *pkt);
int server_broadcast_to_others(server_t *server,
    network_packet_t *pkt, int sender);
void server_close(server_t *server);
int client_init(client_t *client, const char *ip, int port);
int client_send_packet(client_t *client, network_packet_t *packet);
int client_recv_packet(client_t *client, network_packet_t *packet);
void client_close(client_t *client);

#endif
