##
## EPITECH PROJECT, 2026
## makefile
## File description:
## makefile
##

SRC	=	$(shell find . -type f -name "*.c")

OBJ	=	$(SRC:.c=.o)

NAME	=	wolf3d

all:	$(NAME)

$(NAME):	$(OBJ)
	epiclang $(SRC) -o $(NAME) -I./include -lcsfml-graphics -lcsfml-window -lcsfml-system -lm 

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re