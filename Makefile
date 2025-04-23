CC = cc
CFLAGS = -g -Wall -Wextra -Werror
LIBFTDIR = ./libft_v1
M_SRC = execution/execution.c execution/mini_pars.c execution/builtins/echo.c execution/builtins/pwd.c execution/help_func/check_cmd.c execution/help_func/set_data.c \
		execution/help_func/check_builtins_cmd.c execution/help_func/get_env.c execution/builtins/env.c execution/builtins/cd.c #parcing/tokenizer.c
M_OBJ = $(M_SRC:.c=.o)
NAME = minishell
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