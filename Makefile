NAME = minishell

GREEN := \033[1;92m
DEFAULT := \033[0;39m

CC := cc

CFLAGS := -Wall -Wextra -Werror \
	-I ./include -I ./libft/libft -I ./libft/printf

LIBFT := ./libft/libft
PRINTF := ./libft/printf
LIBS := $(LIBFT)/libft.a $(PRINTF)/libftprintf.a -lreadline

SRCS_DIR = ./src
SRCS_SUBDIR = builtin execute pre_handle signal tools
VPATH = $(SRCS_DIR) $(addprefix $(SRCS_DIR)/, $(SRCS_SUBDIR))

SRCS =	main.c \
		cd.c echo.c env.c exit.c export_tools.c export.c unset.c \
		exe.c heredoc.c pipe_redirect.c redirect.c type.c exe_child.c \
		add_cmd_utils.c checking_token_type.c checking.c del_empty_node_extra_pipe.c \
		expander.c lexer.c local_var.c operate_token.c parsing.c pre_handle.c process_re.c \
		handle_signal.c signal.c \
		error.c exe_tools.c free.c path.c restart.c tool.c variable_list.c handle_wave.c

OBJS = $(SRCS:.c=.o)


all: $(NAME)
bonus:$(NAMEB)
$(NAMEB): $(OBJS_B)
	@${MAKE} -C ${LIBFT}
	@${MAKE} -C ${PRINTF}
	@$(CC) $(CFLAGS) $(OBJS_B) $(LIBS) -o $(NAMEB)
	@echo "$(GREEN)minishell_bonus has been generated.$(DEFAULT)"
%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@${MAKE} -C ${LIBFT}
	@${MAKE} -C ${PRINTF}
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)minishell has been generated.$(DEFAULT)"

clean:
	@rm -rf $(OBJS)
	@${MAKE} -C ${LIBFT} clean
	@${MAKE} -C ${PRINTF} clean
	@echo "$(GREEN)OBJS has been cleaned.$(DEFAULT)"

fclean: clean
	@rm -rf $(NAME)
	@${MAKE} -C ${LIBFT} fclean
	@${MAKE} -C ${PRINTF} fclean
	@echo "$(GREEN)minishell has been cleaned.$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean re
