NAME = minirt

libft = libft/libft.a

CC = cc

MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit -lm

CFLAGS = -O3 -Wall -Wextra -Werror #-fsanitize=address -g

SRC = parcing.c\
	gnl/get_next_line.c\
	gnl/get_next_line_utils.c\
	ft_atof.c\
	minirt_split.c\
	check_shapes.c\
	check_shapes_sequel.c\
	check_validation.c\
	minirt.c\
	print.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(libft):
	make -C libft
	@echo "\033[0m"

$(NAME): $(OBJ) $(libft)
	$(Rt)
	@echo "\033[1;36m"
	$(CC) $(MLX_FLAGS) $(CFLAGS) $(OBJ) $(libft) -o $(NAME)
	@echo "\033[0m"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bold : 
	@echo "\033[1;37m"

clean:
	make -C libft clean
	rm -rf $(OBJ)

fclean: clean
	make -C libft fclean
	rm -rf $(NAME)

re: fclean  all

.PHONY: all clean fclean re



define Rt

@echo "\033[1;93m"
@echo "	*---------------------------------------------------------------*"
@echo "	|		            _       _      _			|"
@echo "	|		           (_)     (_)    | |			|"
@echo "	|		  _ __ ___  _ _ __  _ _ __| |_			|"
@echo "	|		 | '_   _ \| | '_ \| | \'__| __|		|"
@echo "	|		 | | | | | | | | | | | |  | |_			|"
@echo "	|		 |_| |_| |_|_|_| |_|_|_|   \__|			|"
@echo "	*---------------------------------------------------------------*"
@echo "\033[0m"

endef
