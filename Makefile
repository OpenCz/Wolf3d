CLIENT_NAME	= wolf3d
SERVER_NAME	= server

CC		= cc
CFLAGS		= -Wall -Wextra -Werror

INCLUDES	= -I include

CLIENT_SRCS	= $(wildcard src/client/*.c) $(wildcard src/shared/*.c)
SERVER_SRCS	= $(wildcard src/server/*.c) $(wildcard src/shared/*.c)

CLIENT_OBJS	= $(CLIENT_SRCS:.c=.o)
SERVER_OBJS	= $(SERVER_SRCS:.c=.o)

all: $(CLIENT_NAME) $(SERVER_NAME)

$(CLIENT_NAME): $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) -o $(CLIENT_NAME)

$(SERVER_NAME): $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(SERVER_OBJS) -o $(SERVER_NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(CLIENT_OBJS) $(SERVER_OBJS)

fclean: clean
	rm -f $(CLIENT_NAME) $(SERVER_NAME)

re: fclean all

.PHONY: all clean fclean re
