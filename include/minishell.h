/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:00:09 by yzheng            #+#    #+#             */
/*   Updated: 2024/10/29 17:23:30 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
# define MEMORY_ERROR		"error: Could not allocate memory"
# define UNQUOTED			"error: The input is quoted incorrectly"
//# define ADD_TOKEN_FAILED	"error: Could not add a new token node to token"
# define PIPE_STX_ERR		"minishell: syntax error near unexpected token `|'"
# define NL_STX_ERR			"minishell: syntax error near unexpected token `newline'"
# define IN_RE_STX_ERR		"minishell: syntax error near unexpected token `<'"
# define OUT_RE_STX_ERR		"minishell: syntax error near unexpected token `>'"
# define HDOC_STX_ERR		"minishell: syntax error near unexpected token `<<'"
# define APED_STX_ERR		"minishell: syntax error near unexpected token `>>'"
# define ADD_CMD_ERR		"error: Could not add a new command node"
# define DEL_TOKEN_ERR		"error: Could not delete a token from the list"


# include <sys/stat.h>
/*For global*/
t_ms	*ms(void);


/*For error*/
int	export_err(char	*cmd);
void	open_error(char *message);
void	ex_error(char *message, t_err_type type, int err_status);
bool	print_error(char *err_type, int err_fd);
bool	stx_error(t_token *node);

/*For shell*/
void	restart(int exit);


/*For	tools*/
void	close_inout();
void	pp_free(char **fly);
void	close_all(int	prev_fd);
void	check_infile(t_cmd *cm);
char	*ft_strndup(char *src, int size);
char	*replace_first_substring(char *str, char *old_sub, char *new_sub);

int		ft_strcmp(char *s1, char *s2);

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
int		ft_env(void);
/*<-----builtin----->*/
int	ft_cd(char **cmd);
int	ft_env(void);
int	ft_unset(char **cmd);
int	ft_echo(char	**cmd);
void	ft_exit(char **cmd);
int	ft_export(char	**cmd);
int	print_sorted_env();
char **sort_env();
char	*get_env(char	*name);
/*<------redirect------->*/
int	set_errors(char *message);
int	check_files(t_cmd *cm);
int		set_fd(t_cmd *cm);
/*                                             pre_handle                                               */

// add_cmd_utils.c
void	count(t_cmd **cmd, t_list *tk_lt, int start, int end);
bool	allocate_mem(t_cmd **cmd);

// checking_token_type.c
bool	is_pipe(t_token *token);
bool	is_dir(t_token *token);
bool	is_dir_or_pipe(t_token *token);
bool	is_seperator(char c);
bool	is_defining_var(char *str);

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
int		add_token(char *str, t_token_type token, bool merge);
t_token	*tk_list_manager(t_list_position psn);
void	del_node(t_list *node);
void	delete_token(t_token *token);

// parsing.c
bool	parsing(void);

// pre_handle.c
bool	pre_handle(void);

// process_re.c
void	process_re(t_cmd **cmd, t_list *tk_node);

//variable_list.c
bool	are_all_def_loc_var(void);
void	del_empty_node_extra_pipe(t_list **list);
void	recorrect_cmd_intype(t_cmd *list);

/*..............................................signal....................................................*/
void	signal_default(void);
void	signal_heredoc(void);
void	signal_child(void);
void	signal_ignore(void);
void	handle_sigint(int signal);
void	handle_heredoc(int signal);

/*..............................................tools..............................................*/
// exe_tools.c
int	count_cm(t_cmd *head);
// utils.c
bool	is_pipe(t_token *token);
bool	is_dir(t_token *token);
bool	is_dir_or_pipe(t_token *token);
bool	is_seperator(char c);

// variable_list.c
t_env	*new_variable(char *name, char *value);
char	*get_variable_value(char *env_name);
void	add_node_to_list(t_list **list, char *str);

// free.c
void	ft_free_str(void *pointer);
void	free_token_list(void);
void	free_cmd_list(void);
void	free_local_var_list(void);
void	free_env(t_env *env);
//void    free_token(t_token *token);



// below are for testing!!!!!!!!!
# define GREEN		"\033[1;32m"
# define RESET_C		"\033[0m"
void	print_list(t_list *list, int flag); // for testing!!!!!!!!!!!11
void	print_cmd(void);// for testing!!!!!!!!!!!11
# endif
