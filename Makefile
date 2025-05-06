NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
RDFLAG = -lreadline

SRCS = src/main.c src/executor/exec_main.c src/utils/init_env.c src/utils/utils.c src/executor/builtins/exec_builtin.c src/executor/builtins/cd_builtin.c \
		src/executor/builtins/exit_builtin.c src/executor/builtins/export_builtin.c src/executor/builtins/echo_builtin.c src/executor/builtins/unset_builtin.c \
		src/executor/redirection.c src/executor/exec_external.c src/utils/command_path.c src/executor/exec_pipe.c src/utils/print_error.c src/utils/free.c 
OBJS = $(SRCS:%.c=%.o)
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

HEADER = include/minishell.h

all : $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(RDFLAG) -o $(NAME)

$(OBJS): %.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): $(LIBFT_DIR)/*.c
	@make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: clean
