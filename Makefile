# Compiler and Flags
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I. -I$(LIBFTDIR)

# Libft
LIBFTDIR = ./libft_v1


# Sources
M_SRC = \
	main.c \
	parcing/tokenizer.c \
	parcing/expand.c \
	parcing/utils.c \
	parcing/syntax.c \
	execution/mini_pars.c \
	execution/builtins/echo.c \
	execution/execution.c \
	execution/builtins/pwd.c \
	execution/help_func/check_cmd.c \
	execution/help_func/set_data.c \
	execution/help_func/check_builtins_cmd.c \
	execution/help_func/get_env.c \
	execution/builtins/env.c \
	execution/builtins/cd.c

# Objects
M_OBJ = $(M_SRC:.c=.o)

# Binary name
NAME = minishell

# Clean
DELETE = rm -f

# Default rule
all: $(NAME)

# Linking
$(NAME): $(M_OBJ)
	$(MAKE) -C $(LIBFTDIR)
	$(MAKE) bonus -C $(LIBFTDIR)
	$(CC) $(CFLAGS) $(M_OBJ) $(LIBFTDIR)/libft.a -lreadline -o $(NAME)

# Compile each .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	$(MAKE) clean -C $(LIBFTDIR)
	$(DELETE) $(M_OBJ)

# Clean all
fclean: clean
	$(MAKE) fclean -C $(LIBFTDIR)
	$(DELETE) $(NAME)

# Rebuild
re: fclean all
