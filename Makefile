CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFTDIR = ./libft_v1
M_SRC = execution/executor.c execution/mini_pars.c execution/builtins/echo.c execution/builtins/pwd.c execution/help_func/check_cmd.c
M_OBJ = $(M_SRC:.c=.o)
NAME = minisheel
DELETE = rm -f

all: $(NAME) 

$(NAME): $(M_OBJ)
	make -C $(LIBFTDIR)
	$(CC) $(CFLAGS) $(M_OBJ) $(LIBFTDIR)/libft.a -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFTDIR)
	$(DELETE) $(M_OBJ)

fclean: clean
	make fclean -C $(LIBFTDIR)
	$(DELETE) $(NAME) $(M_OBJ)

re: fclean all