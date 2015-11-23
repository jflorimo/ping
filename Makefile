NAME =	ft_ping

SRCDIR = srcs/

CFILES =	main.c

SRC = $(addprefix $(SRCDIR), $(CFILES))

GCC = gcc -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

HDDIR = includes/

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/
	@$(GCC) -o $(NAME) $(OBJ) libft/libft.a $(MLX)
	@echo "\033[33m"compilation of $(NAME) : "\033[32m"Success"\033[0m"

%.o: %.c
	@echo -n .
	@$(GCC) -c -o $@ $^  -I $(HDDIR)

clean:
	@make -C libft/ clean
	@rm -f $(OBJ)

fclean: clean
	@make -C libft/ fclean
	@rm -rf $(NAME)
	@echo "\033[31m"$(NAME) : deleted"\033[0m"

re: fclean all

.PHONY: clean fclean re