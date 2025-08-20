CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRC = main.c philo_parcer.c utiles_funs.c philo_funs.c
OBJ = $(SRC:.c=.o)

NAME = philo

all: $(NAME)
	
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re:	fclean all

.PHONY: clean all
