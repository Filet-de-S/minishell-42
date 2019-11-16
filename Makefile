NAME = minishell

CORE = main.c
MOD = strings.c exp.c extra.c built_ins.c built_in_cd_exit.c

OBJ = $(addprefix core/, $(CORE:.c=.o)) \
	  $(addprefix mod/, $(MOD:.c=.o))

all: $(NAME)
$(NAME): libft objdir $(OBJ)
	@gcc -g -L libft/ -lft $(OBJ) -o $(NAME)
	@echo "Minishell is ready to use"

%.o: %.c
	@gcc -Wall -Wextra -Werror -g -I libft/includes -I includes -c $< -o $@
	@echo "new obj created: $@"

objdir:
	@[ -d obj ] || mkdir obj

libft:
	@git submodule init
	@git submodule update
	@make -C libft
	@echo "libft is compiled!"

.PHONY: libft

clean:
	@make -C libft clean
	@rm -rf obj
	@echo "Obj Cleaned!"

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean
	@echo "Full Cleaned!"

re: fclean all
