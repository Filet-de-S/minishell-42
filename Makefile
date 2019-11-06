NAME = minishell

SRC = main.c, string.c

OBJ = $(addprefix obj/, SRC:.c=.o)

all: $(NAME)
$(NAME): libft objdir $(OBJ)
	@gcc -g -L libft -lft $(OBJ) -o $(NAME)
	@echo "Minishell is ready to use"

obj/%.o: %.c
	@gcc -Wall -Wextra -Werror -g -I libft/includes -I includes -c $< -o $@
	@echo "new obj created: $@"

objdir:
	[ -d obj ] || mkdir obj

libft:
	@git submodule init
    @git submodule update
	@$(MAKE) -C libft
	@echo "libft is compiled!"

clean:
	@$(MAKE) -C libft clean
	@rm -rf obj
	@echo "Obj Cleaned!"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C libft fclean
	@echo "Full Cleaned!"


re: fclean all
