##
## EPITECH PROJECT, 2026
## makefile
## File description:
## makefile
##

CC     = epiclang
CFLAGS = -Wall -Wextra -I./include

SRC_SERVER = $(wildcard src/server/*.c)
SRC_CLIENT = $(wildcard src/client/*.c)

all: server client

server: $(SRC_SERVER)
	$(CC) $(CFLAGS) $(SRC_SERVER) -o server_wolf3d -lcsfml-network -lcsfml-system

client: $(SRC_CLIENT)
	$(CC) $(CFLAGS) $(SRC_CLIENT) -o wolf3d -lcsfml-graphics -lcsfml-window -lcsfml-network -lcsfml-system

clean:
	rm -f server wolf3d

fclean: clean
	rm -f server wolf3d

re: fclean all

.PHONY: all clean fclean re