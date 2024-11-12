NAME = minishell
NAMEB = minishell_bonus

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
		exe.c heredoc.c pipe_redirect.c redirect.c type.c \
		add_cmd_utils.c checking_token_type.c checking.c del_empty_node_extra_pipe.c \
		expander.c lexer.c local_var.c operate_token.c parsing.c pre_handle.c process_re.c \
		handle_signal.c signal.c \
		error.c exe_tools.c free.c path.c restart.c tool.c variable_list.c handle_wave.c

OBJS = $(SRCS:.c=.o)

SRCS_DIR_B = ./src_bonus
SRCS_B_BU = $(SRCS_DIR_B)/builtin
SRCS_B_EX = $(SRCS_DIR_B)/execute
SRCS_B_PR = $(SRCS_DIR_B)/pre_handle
SRCS_B_SI = $(SRCS_DIR_B)/signal
SRCS_B_TO = $(SRCS_DIR_B)/tools

SRCS_B = $(SRCS_DIR_B)/main_bonus.c \
		$(SRCS_B_BU)/cd_bonus.c $(SRCS_B_BU)/echo_bonus.c $(SRCS_B_BU)/env_bonus.c $(SRCS_B_BU)/exit_bonus.c \
		$(SRCS_B_BU)/export_tools_bonus.c $(SRCS_B_BU)/export_bonus.c $(SRCS_B_BU)/unset_bonus.c \
		$(SRCS_B_EX)/exe_bonus.c $(SRCS_B_EX)/heredoc_bonus.c $(SRCS_B_EX)/pipe_redirect_bonus.c \
		$(SRCS_B_EX)/redirect_bonus.c $(SRCS_B_EX)/type_bonus.c \
		$(SRCS_B_PR)/add_cmd_utils_bonus.c $(SRCS_B_PR)/checking_token_type_bonus.c \
		$(SRCS_B_PR)/checking_bonus.c $(SRCS_B_PR)/del_empty_node_extra_pipe_bonus.c \
		$(SRCS_B_PR)/expander_bonus.c $(SRCS_B_PR)/lexer_bonus.c $(SRCS_B_PR)/local_var_bonus.c \
		$(SRCS_B_PR)/operate_token_bonus.c $(SRCS_B_PR)/parsing_bonus.c $(SRCS_B_PR)/pre_handle_bonus.c \
		$(SRCS_B_PR)/process_re_bonus.c $(SRCS_B_PR)/handle_wave_bonus.c\
		$(SRCS_B_SI)/handle_signal_bonus.c $(SRCS_B_SI)/signal_bonus.c \
		$(SRCS_B_TO)/error_bonus.c $(SRCS_B_TO)/exe_tools_bonus.c $(SRCS_B_TO)/free_bonus.c \
		$(SRCS_B_TO)/path_bonus.c $(SRCS_B_TO)/restart_bonus.c $(SRCS_B_TO)/tool_bonus.c \
		$(SRCS_B_TO)/variable_list_bonus.c

OBJS_B = $(SRCS_B:.c=.o)

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
	@rm -rf $(OBJS) $(OBJS_B)
	@${MAKE} -C ${LIBFT} clean
	@${MAKE} -C ${PRINTF} clean
	@echo "$(GREEN)OBJS has been cleaned.$(DEFAULT)"

fclean: clean
	@rm -rf $(NAME) $(NAMEB)
	@${MAKE} -C ${LIBFT} fclean
	@${MAKE} -C ${PRINTF} fclean
	@echo "$(GREEN)minishell has been cleaned.$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean re
