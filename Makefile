##
## EPITECH PROJECT, 2026
## makefile
## File description:
## makefile
##

CC = epiclang

CFLAGS = -Iinclude -Wall -Wextra -Wno-deprecated-declarations

LIBS = -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-network -lm

SRC_GAME = $(shell find ./src -type f -name "*.c" ! -name "network_*.c" ! -path "*/network/*") \
           src/network/client/client.c

SRC_SERVER = src/network_server.c src/network/server/server.c \
			 src/network/server/server_close.c src/network/client/client.c

OBJ_GAME = $(SRC_GAME:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)

NAME = wolf3d
NAME_SERVER = server

all: $(NAME) $(NAME_SERVER)

$(NAME): $(OBJ_GAME)
	$(CC) $(OBJ_GAME) -o $(NAME) $(CFLAGS) $(LIBS)

$(NAME_SERVER): $(OBJ_SERVER)
	$(CC) $(OBJ_SERVER) -o $(NAME_SERVER) $(CFLAGS) $(LIBS)

clean:
	rm -f $(OBJ_GAME) $(OBJ_SERVER)

fclean: clean
	rm -f $(NAME) $(NAME_SERVER)

re: fclean all

.PHONY: all clean fclean re