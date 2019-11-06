NAME = minishell

SRC = main.c, string.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): libft 
	@git submodule init
    @git submodule update
	@make -C libft
	@gcc -Wall -Wextra -Werror -I libft/includes -I includes -c $(SRC)
	@mkdir -p $(OBJDIR);
	@mv $(OBJ)
	
	gcc -o $(NAME) $(OBJ) -L lib -lft

libft:
	...rules

clean:
	rm -f $(OBJ)
	make -C lib clean

fclean: clean
	rm -f $(NAME)
	make -C lib fclean

re: fclean all
