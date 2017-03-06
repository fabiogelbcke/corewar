CC = gcc
FLAGS = -Wall -Wextra -Werror
ASM = asm
FILES = asm.c \
		valid_line.c \
		line_type.c \
		utils.c \
		utils2.c \
		utils3.c \
		get_routines.c \
		generate_output.c \
		op.c \
		generate_output_params.c \
		generate_output_params2.c \
		validators_parameters.c \
		print_to_file.c \
		file_name.c \
		get_header.c \
		free_routines.c \
		exit_error.c

F_DIR = srcs
SRCS = $(addprefix $(F_DIR)/, $(FILES))

O_DIR = objs
OBJS = $(addprefix $(O_DIR)/, $(FILES:.c=.o))

HEADER = asm.h op.h
H_DIR = header
INC = $(addprefix $(H_DIR)/, $(HEADER))
INCLUDE = -I $(L_DIR) -I $(H_DIR)

L_DIR = libft
LIB = libft/libft.a
LIBLINK = -L ./$(L_DIR) -lft

all: libft $(ASM)

$(ASM):    $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) -o $@ $(OBJS) $(LIBLINK)
	@echo Project : $(ASM)
	@echo "\t"- Compiler : $(CC)
	@echo "\t"- Flags : $(FLAGS)

$(O_DIR)/%.o: $(F_DIR)/%.c $(INC)
	@mkdir -p $(O_DIR)
	@$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $<
	@echo "Creation de "$@" OK"

libft:
	@make -C $(L_DIR)

clean:
	@rm -rf $(O_DIR)
	@$(MAKE) -C ./libft clean

fclean:    clean
	@rm -f $(ASM)
	@$(MAKE) -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re libft
