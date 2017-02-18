CC = gcc

FLAGS = -Wall -Wextra -Werror -g

SRC =	asm.c \
	valid_line.c \
	line_type.c \
	utils.c \
	get_routines.c \
	generate_output.c \
	op.c \
	generate_output_params.c \
	validators_parameters.c \
	print_to_file.c 

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
