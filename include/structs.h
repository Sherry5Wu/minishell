/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:57:07 by jingwu            #+#    #+#             */
/*   Updated: 2024/09/26 11:27:26 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
#include "minishell.h"
# include <stdbool.h>

typedef enum e_token_type
{
	TK_NONE,
	TK_PIPE,
	TK_IN_RE,
	TK_OUT_RE,
	TK_HDOC,
	TK_APPEND,
	TK_SINGLE_QT,
	TK_DOUBLE_QT,
	TK_KEYWORD,
	TK_LOC_V,
}	t_token_type;

typedef struct s_lexer
{
	char			*str;
	t_token_type	token;
	int				index;
	struct s_lexer	*next;
	struct s_lexer	*pre;
}	t_lexer;

typedef struct s_parser
{
	t_lexer			*s_lexer_list;
	t_lexer			*redirections;
	int				num_rdrct;
	struct s_tools	*tools;
}	t_parser;

// typedef struct s_tools
// {
// 	char					*args;
// 	char					**paths;
// 	char					**envp;
// 	struct s_simple_cmds	*simple_cmds;
// 	t_lexer					*lexer_list;
// 	char					*pwd;
// 	char					*old_pwd;
// 	int						num_pipe;
// 	int						*pid;
// 	bool					heredoc;
// 	bool					reset;
// }	t_tools;

typedef struct s_ms
{
int	in_fd;
int	out_fd;
int	fd[2];
int	exit;
int	lines;
char **env;
char	*cwd;
char	*prompt;
char	*input;
char *path;
pid_t	pipeid[2];
}   t_ms;

typedef struct s_cmd
{
	char			**cmd;
	char			*infile;
	char			**outfile;
	t_token_type	intype;
	t_token_type	outype;
	int				ispipe;
	int				prepipe;
	int				ofnum;
	struct s_cmd	*next;
}	t_cmd;

typedef enum s_error
{
	DIRECTORY,
	NFILE,
	COMMAND,
	ERR,
}	t_error;

# endif
