NAME = minirt

libft = libft/libft.a

lib_point = lib_point/libpoint.a

CC = cc

MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit -lm

CFLAGS = -O3 -Wall -Wextra -Werror


RAY_SRC = $(addprefix raytracing/, mlx_func.c utils.c cylindre.c free.c sphere.c plan.c capsule.c camera.c map.c raytrace.c)

SRC = gnl/get_next_line.c\
	gnl/get_next_line_utils.c\
	parsing/check_file_rt.c\
	parsing/check_shapes_sequel_two.c\
	parsing/check_shapes_sequel.c\
	parsing/parsing.c\
	parsing/ft_atof.c\
	parsing/minirt_split.c\
	parsing/check_shapes.c\
	parsing/check_validation.c\
	minirt.c\
	$(RAY_SRC)

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(libft):
	@echo "\033[0m"
	make -C libft

$(lib_point):
	make -C lib_point


$(NAME): $(OBJ) $(libft) $(lib_point)
	$(Rt)
	@echo -n "\033[1;36m"
	$(CC) $(MLX_FLAGS) $(CFLAGS) $(OBJ) $(libft) $(lib_point) -o $(NAME)
	@echo "\033[0m"

%.o: %.c
	@echo "\033[0m"
	$(CC) $(CFLAGS) -c $< -o $@

bold : 
	@echo "\033[1;37m"

clean:
	make -C libft clean
	make -C lib_point clean
	rm -rf $(OBJ)

fclean: clean
	@echo "\033[0;31m"
	make -C libft fclean
	make -C lib_point fclean
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
