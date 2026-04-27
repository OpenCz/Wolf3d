/*
** EPITECH PROJECT, 2026
** network
** File description:
** standalone client
*/

#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include "../include/network.h"

static int running = 1;
static pid_t game_pid = -1;

static void stop_game(void)
{
	if (game_pid > 0) {
		kill(game_pid, SIGTERM);
		waitpid(game_pid, NULL, 0);
		game_pid = -1;
	}
}

void signal_handler(int sig)
{
	(void)sig;
	running = 0;
	stop_game();
}

static int launch_game(void)
{
	pid_t pid = fork();

	if (pid < 0)
		return -1;
	if (pid == 0) {
		execl("./wolf3d", "wolf3d", NULL);
		exit(1);
	}
	game_pid = pid;
	sleep(1);
	return 0;
}

static void send_position(client_t *client, float x, float y, float angle)
{
	network_packet_t pkt;

	memset(&pkt, 0, sizeof(pkt));
	pkt.type = PKT_PLAYER_POS;
	pkt.player_id = client->player_id;
	pkt.timestamp = time(NULL);
	pkt.x = x;
	pkt.y = y;
	pkt.angle = angle;
	client_send_packet(client, &pkt);
}

static void drain_incoming(client_t *client)
{
	network_packet_t pkt;

	while (client_recv_packet(client, &pkt) > 0);	
}

static int game_stopped(void)
{
	int status;

	if (game_pid <= 0)
		return 0;
	if (waitpid(game_pid, &status, WNOHANG) <= 0)
		return 0;
	game_pid = -1;
	return 1;
}

int main(void)
{
	client_t client;
	float x = 100.0f;
	float y = 100.0f;
	float angle = 0.0f;

	signal(SIGINT, signal_handler);
	if (client_init(&client, "127.0.0.1", PORT) < 0)
		return 1;
	if (launch_game() < 0) {
		client_close(&client);
		return 1;
	}
	while (running) {
		x += 0.5f;
		angle += 0.01f;
		send_position(&client, x, y, angle);
		drain_incoming(&client);
		if (game_stopped())
			running = 0;
		sleep(1);
	}
	stop_game();
	client_close(&client);
	return 0;
}
