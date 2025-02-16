NAME		= philo

CC			= gcc
RM			= rm -f

FLAGS		= -Wall -Wextra -Werror -pthread -Iinc

SRCS 		= \
./src/utils.c ./src/error.c ./src/init.c ./src/philo.c \

OBJS 		= $(SRCS:.c=.o)

.c.o:
			@$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

all :		$(NAME)

$(NAME) :	${OBJS}
			@echo "philo..."
			@${CC} ${OBJS} $(FLAGS) -o ${NAME}

clean:
			@echo "Cleaning..."
			@rm -f $(OBJS)

fclean:		clean
			@echo "Cleaning all..."
			@rm -f $(NAME)

re: 		fclean all

.PHONY : all clean fclean re
