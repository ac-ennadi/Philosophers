CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c philo_parcer.c utiles_funs.c

NAME = philo

all:
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re:	fclean all

.PHONY: clean all