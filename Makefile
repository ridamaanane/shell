CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = execution_part/builtins/do_cd.c execution_part/builtins/do_echo.c execution_part/builtins/do_env.c execution_part/builtins/do_exit.c execution_part/builtins/do_export.c \
	execution_part/builtins/do_pwd.c execution_part/builtins/do_unset.c execution_part/builtins/print_env.c \
	execution_part/execute_external.c execution_part/redirections.c execution_part/pipe_executor.c execution_part/execution/main.c   


OBJ = $(SRC:%.c=%.o)
NAME = minishell
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)


clean:
	@$(RM) $(OBJ)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)


all: libft_rule $(NAME)
libft_rule:
	@$(MAKE) -C $(LIBFT_DIR)

re: fclean all

.SECONDARY: $(OBJ)
.PHONY: all clean fclean re bonus