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
	$(CC) $(CFLAGS) -o server -lcsfml-network -lcsfml-system

client: $(SRC_CLIENT)
	$(CC) $(CFLAGS) -o wolf3d -lcsfml-graphics -lcsfml-window -lcsfml-network -lcsfml-system

clean:
	rm -f server client

fclean: clean
	rm -f server client

re: fclean all

.PHONY: all clean fclean re