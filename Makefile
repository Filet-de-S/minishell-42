NAME = minishell

SRC = main.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	make -C lib
	gcc -Wall -Wextra -Werror -I lib/includes -c $(SRC)
	gcc -o $(NAME) $(OBJ) -L lib -lft

clean:
	rm -f $(OBJ)
	make -C lib clean

fclean: clean
	rm -f $(NAME)
	make -C lib fclean

re: fclean all
