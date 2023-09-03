NAME = miniRt

NAME_BONUS = miniRt_bonus

libft = mandatory/libft/libft.a

lib_point = mandatory/lib_point/libpoint.a

libft_bonus = bonus/libft/libft.a

lib_point_bonus = bonus/lib_point/libpoint.a

CC = cc

MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit -lm -O3

CFLAGS =  -Wall -Wextra -Werror #-fsanitize=address -g

RAY_SRC = $(addprefix raytracing/, mlx_func.c utils.c cylindre.c free.c sphere.c plan.c camera.c map.c raytrace.c)

RAY_SRC_BONUS = $(addprefix raytracing/, mlx_func.c utils.c cylindre.c free.c sphere.c plan.c camera.c map.c raytrace.c capsule.c)

SRC = $(addprefix mandatory/, gnl/get_next_line.c gnl/get_next_line_utils.c parsing/check_file_rt.c parsing/check_shapes_sequel_two.c parsing/check_shapes_sequel.c parsing/parsing.c parsing/ft_atof.c parsing/minirt_split.c parsing/check_shapes.c parsing/check_validation.c minirt.c $(RAY_SRC))

SRC_BONUS = $(addprefix bonus/, gnl/get_next_line.c gnl/get_next_line_utils.c parsing/check_file_rt.c parsing/check_shapes_sequel_two.c parsing/check_shapes_sequel.c parsing/parsing.c parsing/ft_atof.c parsing/minirt_split.c parsing/check_shapes.c parsing/check_validation.c minirt.c $(RAY_SRC_BONUS))

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME)

$(libft):
	@echo "\033[0m"
	make -C mandatory/libft

$(lib_point):
	make -C mandatory/lib_point

$(NAME): $(OBJ) $(libft) $(lib_point)
	$(Rt)
	@echo "\033[1;36m"
	$(CC) $(MLX_FLAGS) $(CFLAGS) $(OBJ) $(libft) $(lib_point) -o $(NAME)
	@echo "\033[0m"

%.o: %.c
	@echo "\033[0m"
	$(CC) $(CFLAGS) -c $< -o $@

bold : 
	@echo "\033[1;37m"


bonus : $(NAME_BONUS)

$(libft_bonus):
	@echo "\033[0m"
	make -C bonus/libft

$(lib_point_bonus):
	make -C bonus/lib_point

$(NAME_BONUS): $(OBJ_BONUS) $(libft_bonus) $(lib_point_bonus)
	$(Rt)
	@echo "\033[1;36m"
	$(CC) $(MLX_FLAGS) $(CFLAGS) $(OBJ_BONUS) $(libft_bonus) $(lib_point_bonus) -o $(NAME_BONUS)
	@echo "\033[0m"

clean:
	make -C mandatory/libft clean
	make -C mandatory/lib_point clean
	make -C bonus/libft clean
	make -C bonus/lib_point clean
	rm -rf $(OBJ)
	rm -rf $(OBJ_BONUS)

fclean: clean
	@echo "\033[0;31m"
	make -C mandatory/libft fclean
	make -C mandatory/lib_point fclean
	make -C bonus/libft fclean
	make -C bonus/lib_point fclean
	rm -rf $(NAME)
	rm -rf $(NAME_BONUS)

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
