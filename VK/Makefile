NAME			= philosophers

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread -o3 -g -fsanitize=address

SRC = utils.c \
		time.c \
		input_valid.c \
		handle_philo.c \
		routine.c \
		prints.c \
		create.c \
		destroy.c \
		threads.c \
		main.c 
			 	


OBJ = ${SRC:.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:			all clean fclean re
