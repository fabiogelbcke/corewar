CC = gcc

FLAGS = -Wall -Wextra -Werror -g

SRC =	asm.c

OBJ	= $(SRC:.c=.o)

LIB 	= libft/libft.a

NAME = asm

all:		$(NAME)

$(NAME):	$(OBJ)
	$(MAKE) -C ./libft
	$(CC) -o $(NAME) $(FLAGS) $(OBJ) $(LIB)

clean:
	rm -f $(OBJ)
	$(MAKE) -C ./libft clean

fclean:	clean
	rm -f $(NAME)
	$(MAKE) -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re
