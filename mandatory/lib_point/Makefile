SRCS	= 3d_operation.c  3d_operation2.c 3d_operation3.c 3d_space_calcs.c angle.c

OBJS	= ${SRCS:.c=.o}

NAME	= libpoint.a

CC		= cc

CFLAGS	= -Wall -Wextra -Werror #-g -fsanitize=address

RM		= rm -f

AR    = ar rc

%.o: %.c
			${CC} ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS}
		  ${AR} ${NAME} ${OBJS}
			ranlib ${NAME}

all:		${NAME}

clean:
			${RM} ${OBJS} ${OBJS_BONUS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all
