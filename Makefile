NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = main.c parser.c init.c ft_atoi.c threads.c time.c\
		utils.c actions.c monitor_utils.c routine_utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c philosophers.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re