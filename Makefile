# Compiler and Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -I$(LIBFTDIR) 

# Libft
LIBFTDIR = ./libft_v1


# Sources
M_SRC = \
	main.c \
	parcing/tokenizer.c \
	parcing/parse.c \
	parcing/expand.c \
	parcing/utils.c \
	parcing/syntax.c \
	execution/mini_pars.c \
	execution/builtins/echo.c \
	execution/builtins/exit.c \
	execution/external_cmd/external_cmd.c \
	execution/external_cmd/help_func2/fond_cmd.c \
	execution/external_cmd/help_func2/get_path_variable.c \
	execution/execution.c \
	execution/builtins/pwd.c \
	execution/builtins/unset.c \
	execution/help_func/check_cmd.c \
	execution/help_func/get_cpy_of_env.c \
	execution/help_func/sort_arr.c \
	execution/help_func/get_value_and_key.c \
	execution/help_func/print_expo.c \
	execution/help_func/get_clean_key.c \
	execution/help_func/set_data.c \
	execution/help_func/check_builtins_cmd.c \
	execution/help_func/valid_key.c \
	execution/help_func/get_env.c \
	execution/builtins/env.c \
	execution/builtins/cd.c \
	execution/builtins/export.c \

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
