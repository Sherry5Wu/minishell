/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:00:09 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/14 11:13:06 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
	<stdbool.h>	bool type;
	<readline/readline.h>	readline();
	<readline/readline.h>	operate the readline history;
	<fcntl.h>	the flags when open a file;
	<signal.h>	the signal functions;
	<unistd.h>	for STDERR_FILENO
*/
# include "../libft/libft/libft.h"
# include "../libft/printf/printf.h"
# include "./structs.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

/*err_type */
# define MEMORY_ERROR "error: Could not allocate memory"
# define UNQUOTED "error: The input is quoted incorrectly"
# define PIPE_STX_ERR "minishell: syntax error near unexpected token `|'"
# define NL_STX_ERR "minishell: syntax error near unexpected token `newline'"
# define IN_RE_STX_ERR "minishell: syntax error near unexpected token `<'"
# define OUT_RE_STX_ERR "minishell: syntax error near unexpected token `>'"
# define HDOC_STX_ERR "minishell: syntax error near unexpected token `<<'"
# define APED_STX_ERR "minishell: syntax error near unexpected token `>>'"
# define ADD_CMD_ERR "error: Could not add a new command node"
# define DEL_TOKEN_ERR "error: Could not delete a token from the list"

/*<--------------------------------builtin--------------------------------->*/
// cd.c
int		ft_cd(char **cmd);
char	*get_env(char *name);
// echo.c
int		ft_echo(char **cmd);
// env.c
int		ft_env(void);
// exit.c
void	ft_exit(char **cmd);
// export_tools.c
void	bubble_sort(char **env, int count);
char	**sort_env(void);
bool	ft_valid_character(char *str);
int		count_array_size(char **str);
void	add_env(char *str);
// export.c
int		ft_export(char **cmd);
// unset.c
int		ft_unset(char **cmd);

/*<--------------------------------execute--------------------------------->*/
/*For error*/
int		export_err(char *cmd);
void	open_error(char *message);
void	ex_error(char *message, t_err_type type, int err_status);
bool	print_error(char *err_type, int err_fd);
bool	stx_error(t_token *node);

/*For shell*/
void	restart(int exit);

/*For	tools*/
void	close_inout(void);
void	pp_ft_free_str(char **fly);
void	close_all(int prev_fd);
void	check_infile(t_cmd *cm);
char	*ft_strndup(char *src, int size);
char	*replace_first_substring(char *str, char *old_sub, char *new_sub);
char	*prompt(void);
char	*findpath(char **env);
int		ft_strcmp(char *s1, char *s2);
int		print_sorted_env(void);
/*global*/
t_ms	*ms(void);
/*For execute*/
/*<-----pipe && redirect----->*/
void	get_status(pid_t pid);
pid_t	exe_pipe(t_cmd *cm);
pid_t	exe_pipe2(t_cmd *cm);
pid_t	exe_pipe3(t_cmd *cm);
pid_t	type_hdoc(t_cmd *cm);
pid_t	type_outpipe(t_cmd *cm, int *prev_fd);
/*<-----exe----->*/
void	exe_final(void);
char	*findvalidcmd(char **shellcmd);
void	real_execute(t_cmd *cm);
void	exe(t_cmd *cm);
int		ft_env(void);
void	heredoc(t_cmd *cm);
int		builtin(char **cmd);
/*<------redirect------->*/
int		set_errors(char *message);
int		set_fd(t_cmd *cm);
/*    pre_handle  */

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

// variable_list.c
bool	are_all_def_loc_var(void);
void	del_empty_node_extra_pipe(t_list **list);
void	recorrect_cmd_intype(t_cmd *list);

bool	handle_wave_sign(t_list *list);

/*..signal...*/
void	signal_default(void);
void	signal_heredoc(void);
void	signal_child(void);
void	signal_ignore(void);
void	handle_sigint(int signal);
void	handle_heredoc(int signal);

// exe_tools.c
int		count_cm(t_cmd *head);
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
void	free_cmd_list(void);
void	free_local_var_list(void);
void	free_env(t_env *env);

#endif
