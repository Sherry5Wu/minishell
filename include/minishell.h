
#ifndef MINISHELL_H
# define MINISHELL_H

/*
	<stdio.h>:	printf();
	<stdbool.h>	bool type;
	<readline/readline.h>	readline();
	<readline/readline.h>	operate the readline history;
	<fcntl.h>	the flags when open a file;
	<signal.h>	the signal functions;
	<unistd.h>	for STDERR_FILENO
*/
# include "../libft/libft/libft.h"
# include "../libft/printf/printf.h"
# include "../libft/get_next_line/get_next_line.h"
# include "./structs.h"
# include <stdio.h>
# include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

/*                                             err_type                                         */
# define MEMORY_ERROR		"Unable to allocate memory."
# define UNQUOTED			"The input is quoted incorrectly."
# define ADD_TOKEN_FAILED	"Failed when trying to add a new node to token list."
# define PIPE_STX_ERR		"minishell: syntax error near unexpected token `|'"
# define NL_STX_ERR			"minishell: syntax error near unexpected token `newline'"
# define IN_RE_STX_ERR		"minishell: syntax error near unexpected token `<'"
# define OUT_RE_STX_ERR		"minishell: syntax error near unexpected token `>'"
# define HDOC_STX_ERR		"minishell: syntax error near unexpected token `<<'"
# define APED_STX_ERR		"minishell: syntax error near unexpected token `>>'"
# define ADD_CMD_ERR		"Failed to add a new command node"


/*For global*/
t_ms	*ms(void);


/*For error*/

void	open_error(char *message);
void	ex_error(char *message, t_err_type type, int err_status);

/*For shell*/
void	restart(int exit);

void	test();
/*For	tools*/
void	close_inout();
void	pp_free(char **fly);
void	close_all(int	prev_fd);
void	check_infile(t_cmd *cm);
char	*ft_strndup(char *src, int size);
char *replace_first_substring(char *str, char *old_sub, char *new_sub);
void	set_fd(t_cmd *cm);
/*For execute*/
/*<-----pipe && redirect----->*/

pid_t	exe_pipe(t_cmd *cm);
pid_t	exe_pipe2(t_cmd *cm);
pid_t	exe_pipe3(t_cmd *cm);
void	type_hdoc(t_cmd *cm);
pid_t	type_outpipe(t_cmd *cm, int	*prev_fd);
/*<-----exe----->*/
char	*findvalidcmd(char **shellcmd);
void	real_execute(t_cmd *cm);
void	exe(t_cmd *cm);


/*                                             pre_handle                                               */

// add_cmd_utils.c
void	count(t_cmd **cmd, t_list *tk_lt, int start, int end);
bool	allocate_mem(t_cmd **cmd);

// checking_token_type.c
bool	is_pipe(t_token *token);
bool	is_dir(t_token *token);
bool	is_dir_or_pipe(t_token *token);
bool	is_seperator(char c);
bool	is_defining_var(t_token *token);

// checking.c
bool	check_syntax(void);
bool	check_quote(void);
bool	check_mergerable(char *matcher, char *str, int index);

// expander.c
void	expander(void);

// lexer.c
bool	lexer(void);

// operate_token.c
t_token	*new_token(char *str, t_token_type tk_type, bool merge);
int	add_token(char *str, t_token_type token, bool merge);
t_token	*tk_list_manager(t_list_position psn);
void	del_node(t_list **list, t_list *node);


// parsing.c
bool	parsing(void);

// pre_handle.c
void	restruct_token(void);
bool	pre_handle(void);

// process_re.c
void	process_re(t_cmd **cmd, t_list *tk_node);

/*                                              tools                                                    */
// handle_error.c
bool	print_error(char *err_type, int err_fd);
bool	stx_error(t_token *node);

// utils.c
bool	is_pipe(t_token *token);
bool	is_dir(t_token *token);
bool	is_dir_or_pipe(t_token *token);
bool	is_seperator(char c);

// env_list.c
char	*get_env_value(char *env_name);
void	add_env_node(t_list **list, char *str);

// free.c
void	ft_newfree(void *pointer);

# endif
