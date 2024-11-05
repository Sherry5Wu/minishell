NAME = minishell

GREEN := \033[1;92m
DEFAULT := \033[0;39m

CC := cc
#-g -fsanitize=address for debugging
# CFLAGS := -Wall -Wextra -Werror -g -fsanitize=address \
# 	-I ./include -I ./libft/libft -I ./libft/printf -I ./libft/get_next_line

CFLAGS := -Wall -Wextra -Werror \
	-I ./include -I ./libft/libft -I ./libft/printf -I ./libft/get_next_line


LIBFT := ./libft/libft
PRINTF := ./libft/printf
GETNEXTLINE := ./libft/get_next_line
LIBS := $(LIBFT)/libft.a $(PRINTF)/libftprintf.a $(GETNEXTLINE)/get_next_line.a -lreadline

SRCS_DIR = ./src
SRCS_PDIR = pre_handle
SRCS_SDIR = signal
SRCS_TDIR = tools
SRCS_EDIR = execute
SRCS_BUIL = builtin

SRCS = $(wildcard $(SRCS_DIR)/*.c) \
		$(wildcard $(SRCS_DIR)/$(SRCS_PDIR)/*.c) \
		$(wildcard $(SRCS_DIR)/$(SRCS_SDIR)/*.c) \
		$(wildcard $(SRCS_DIR)/$(SRCS_TDIR)/*.c) \
		$(wildcard $(SRCS_DIR)/$(SRCS_EDIR)/*.c) \
		$(wildcard $(SRCS_DIR)/$(SRCS_BUIL)/*.c)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@${MAKE} -C ${LIBFT}
	@${MAKE} -C ${PRINTF}
	@${MAKE} -C ${GETNEXTLINE}
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)minishell has been generated.$(DEFAULT)"

clean:
	@rm -rf $(OBJS)
	@${MAKE} -C ${LIBFT} clean
	@${MAKE} -C ${PRINTF} clean
	@${MAKE} -C ${GETNEXTLINE} clean
	@echo "$(GREEN)OBJS has been cleaned.$(DEFAULT)"

fclean: clean
	@rm -rf $(NAME)
	@${MAKE} -C ${LIBFT} fclean
	@${MAKE} -C ${PRINTF} fclean
	@${MAKE} -C ${GETNEXTLINE} fclean
	@echo "$(GREEN)minishell has been cleaned.$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean re
