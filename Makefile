NAME = minishell

CORE = main.c
MOD = strings.c exp.c extra.c built_ins.c built_in_cd_exit.c

OBJ = $(addprefix obj/, $(addprefix core/, $(CORE:.c=.o)) $(addprefix mod/, $(MOD:.c=.o)))

all: $(NAME)
$(NAME): libft objdir $(OBJ)
	@gcc -g -L libft/ -lft $(OBJ) -o $(NAME)
	@echo "Minishell is ready to use"

obj/%.o: %.c
	@gcc -Wall -Wextra -Werror -g -I libft/includes -I includes -c $< -o $@
	@echo "msh–> new obj created: $@"

objdir:
	@[ -d obj ] || mkdir obj
	@[ -d obj/core ] || mkdir obj/core
	@[ -d obj/mod ] || mkdir obj/mod

libft:
	@git submodule init
	@git submodule update --remote --merge
	@make -C libft
	@#git submodule update

.PHONY: libft

clean:
	@make -C libft clean
	@rm -rf obj
	@echo "msh–> objs cleaned!"

fclean: clean
	@rm -rf $(NAME) $(NAME).dSYM
	@make -C libft fclean
	@echo "msh–> full cleaned!"

re: fclean all
