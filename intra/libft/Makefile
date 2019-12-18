NAME = ./libft.a

SRC = ft_memset.c \
	  ft_putendl.c \
	  ft_lstdelone.c \
	  ft_lstnew.c \
	  ft_lstdel.c \
	  ft_lstadd.c \
	  ft_lstaddend.c \
	  ft_lstiter.c \
	  ft_lstmap.c \
	  ft_putendl_fd.c \
	  ft_putchar_fd.c \
	  ft_putstr_fd.c \
	  ft_putnbr.c \
	  ft_putnbr_fd.c \
	  ft_bzero.c \
	  ft_putstr.c \
	  ft_memdl.c \
	  ft_putchar.c \
	  ft_itoa.c \
	  ft_strsplit.c \
	  ft_strtrim.c \
	  ft_strjoin.c \
	  ft_strsub.c \
	  ft_strequ.c \
	  ft_strnequ.c \
	  ft_strmap.c \
	  ft_strmapi.c \
	  ft_striter.c \
	  ft_striteri.c \
	  ft_memmove.c \
	  ft_strlen.c \
	  ft_memcpy.c \
	  ft_memccpy.c \
	  ft_memchr.c \
	  ft_memcmp.c \
	  ft_strdup.c \
	  ft_strcpy.c \
	  ft_strncpy.c \
	  ft_atoi.c \
	  ft_isalpha.c \
	  ft_isdigit.c \
	  ft_strcat.c \
	  ft_strchr.c \
	  ft_strcmp.c \
	  ft_strlcat.c \
	  ft_strncat.c \
	  ft_strncmp.c \
	  ft_strnstr.c \
	  ft_strrchr.c \
	  ft_strstr.c \
	  ft_isalnum.c \
	  ft_isascii.c \
	  ft_isprint.c \
	  ft_toupper.c \
	  ft_tolower.c \
	  ft_memalloc.c \
	  ft_memdel.c \
	  ft_strnew.c \
	  ft_strdel.c \
	  ft_strclr.c \
	  ft_strdl.c \
	  ft_sfstrjoin.c \
	  get_next_line.c \
	  get_next_char.c \
	  is_whitespaces.c \
	  ft_strsplitwhites.c

OBJ = $(addprefix obj/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): obj/ $(OBJ)
	@ar rc $@ $(OBJ)
	@ranlib $@

obj/%.o: %.c
	@gcc -Wall -Wextra -Werror -g -I includes/ -c $< -o $@
	@echo "libft–> new obj created: $@"

obj/:
	@mkdir obj

clean:
	@rm -rf obj
	@echo "libft–> objs cleaned!"

fclean: clean
	@rm -f $(NAME)
	@echo "libft–> full cleaned!"

re: fclean all
