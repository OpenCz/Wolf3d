NAME		= wolf3d

CC		= cc
CFLAGS		= -Wall -Wextra -Werror

SRCS		= $(wildcard src/**/*.c) $(wildcard src/*.c)
OBJS		= $(SRCS:.c=.o)

INCLUDES	= -I include

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
