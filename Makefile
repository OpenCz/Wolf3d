NAME		= wolf3d

CC		= cc
CFLAGS		= -Wall -Wextra -Werror

SRCS		= $(shell find src -name '*.c')
OBJS		= $(SRCS:.c=.o)

INCLUDES	= -I include

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
