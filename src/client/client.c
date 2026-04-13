/*
** EPITECH PROJECT, 2026
** client
** File description:
** client
*/

#include "network.h"
#include <SFML/Graphics.h>
#include <stdlib.h>
#include <time.h>

static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 600;
static const float SQUARE_SIZE = 120.0f;

static sfColor random_color(void)
{
    return sfColor_fromRGB(rand() % 256, rand() % 256, rand() % 256);
}

static void center_square(sfRenderWindow *window, sfRectangleShape *square)
{
    sfVector2u win_size = sfRenderWindow_getSize(window);
    sfVector2f pos = {
        (win_size.x - SQUARE_SIZE) / 2.0f,
        (win_size.y - SQUARE_SIZE) / 2.0f
    };

    sfRectangleShape_setPosition(square, pos);
}

static int init_socket(sfTcpSocket **socket, const char *ip)
{
    *socket = sfTcpSocket_create();
    if (*socket == NULL)
        return 84;
    if (sfTcpSocket_connect(*socket, sfIpAddress_fromString(ip),
            PORT_TCP, sfTime_Zero) == sfSocketDone)
        printf("Connecte au serveur !\n");
    else
        printf("Echec de la connexion.\n");
    return 0;
}

static int init_window(sfRenderWindow **window, sfRectangleShape **square)
{
    sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};

    *window = sfRenderWindow_create(mode, "Wolf3d", sfResize | sfClose, NULL);
    if (*window == NULL)
        return 84;
    *square = sfRectangleShape_create();
    if (*square == NULL) {
        sfRenderWindow_destroy(*window);
        return 84;
    }
    sfRectangleShape_setSize(*square, (sfVector2f){SQUARE_SIZE, SQUARE_SIZE});
    sfRectangleShape_setFillColor(*square, sfWhite);
    center_square(*window, *square);
    return 0;
}

static void handle_event(sfRenderWindow *window, sfRectangleShape *square,
    sfEvent event)
{
    sfFloatRect bounds = sfRectangleShape_getGlobalBounds(square);

    if (event.type == sfEvtClosed)
        sfRenderWindow_close(window);
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
        sfRenderWindow_close(window);
    if (event.type == sfEvtResized)
        center_square(window, square);
    if (event.type == sfEvtMouseButtonPressed &&
        event.mouseButton.button == sfMouseLeft &&
        sfFloatRect_contains(&bounds, (float)event.mouseButton.x,
            (float)event.mouseButton.y))
        sfRectangleShape_setFillColor(square, random_color());
}

static void draw_frame(sfRenderWindow *window, sfRectangleShape *square)
{
    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_drawRectangleShape(window, square, NULL);
    sfRenderWindow_display(window);
}

static void run_window_loop(sfRenderWindow *window, sfRectangleShape *square)
{
    sfEvent event;

    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event))
            handle_event(window, square, event);
        draw_frame(window, square);
    }
}

static void destroy_resources(sfTcpSocket *socket, sfRenderWindow *window,
    sfRectangleShape *square)
{
    sfRectangleShape_destroy(square);
    sfRenderWindow_destroy(window);
    sfTcpSocket_disconnect(socket);
    sfTcpSocket_destroy(socket);
}

int main(int argc, char **argv)
{
    const char *ip = argc > 1 ? argv[1] : "127.0.0.1";
    sfTcpSocket *socket = NULL;
    sfRenderWindow *window = NULL;
    sfRectangleShape *square = NULL;

    if (init_socket(&socket, ip) != 0)
        return 84;
    srand((unsigned int)time(NULL));
    if (init_window(&window, &square) != 0) {
        sfTcpSocket_destroy(socket);
        return 84;
    }
    run_window_loop(window, square);
    destroy_resources(socket, window, square);
    return 0;
}
