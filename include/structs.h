/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:57:07 by jingwu            #+#    #+#             */
/*   Updated: 2024/11/11 08:46:28 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"
# include <stdbool.h>

/*
	TK_LOC_V: for defining local variable command, like if input is
	"echo a | name=sherry" then for 'name=sherry' the type of the token 
	is TK_LOC_V.
	For this type,we do NOT put them into cmd list.
*/
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
	TK_WORD,
	TK_LOC_V,
	TK_ENV_V,
}	t_token_type;

typedef enum e_err_type
{
	CMD,
	STX,
	F_NAME,
	DIRECTORY,
	NFILE,
	COMMAND,
	ERR,
	MALLOC,
	PIPE,
	FORK,
	PREMISSON,
	TOOMUCH,
	HOME,
	CD,
}	t_err_type;

/*
	To tell which node you want to pointer to in a link list;
	RESET: reset the pointer points the start of the list;
	NEXT: pointer moves to the next node in the list;
	CUR_COT: return (the content of the current node);
	PRE_COT: return (the content of the next node);
*/
typedef enum e_list_position
{
	RESET,
	NEXT,
	CUR_CNT,
	NEXT_CNT,
}			t_list_position;

/*
	It is for environment variables and local variables
*/
typedef struct e_env
{
	char			*name;
	char			*value;
}	t_env;

/*
	@What is a token?
	It might be a command, a word or a redirector,and so on. Such as "echo",
		"hello", "<";

	@param
	str:	the content of a token, such as "echo", "abd" or "|";
	token:	the type of a token, such as "TK_PIPE" or "TK_APPEND"
	arg:	saving the file name(for <, > or <<) or delimiter (for <<)
	idx:	the index of the token;
*/
typedef struct s_token
{
	char			*str;
	t_token_type	tk_type;
	char			*arg;
	bool			merge;
	int				idx;
}	t_token;

/*
	@param
	prompt:	the message showing in the shell
	input:	the commands that user input from terminal;
	tokens:	the token link list;
	cmds:	the command link list;
*/
typedef struct s_ms
{
	int				heredoc_count;
	int				limiter_count;
	int				in_fd;
	int				out_fd;
	int				fd[2];
	int				exit;
	int				lines;
	int				hstatus;
	pid_t			pipeid[2];
	int				hfd;
	char			**env;
	char			*cwd;
	char			*prompt;
	char			*input;
	char			*path;
	struct s_list	*tokens;
	struct s_list	*env_list;
	struct s_list	*local_var;
	struct s_cmd	*cmds;
	char			**file_error;
	int				err;
}	t_ms;

/*
	@param
	cmd:	the dyadic array of cmds. like "ls
			-l" will be stored as cmd[0]="ls", cmd[1]="-l"
	infile:	the dyadic array of infiles;
	limiter:	the dyadic array of delimiters, coming with '<<';
	outfile:	the dyadic array of outfiles;
	of:		the last outfile name in the part of input seperated by '|'.
			For example, the input :"echo a >3 >>4 >5 | ...."
			in this case, of = "5";

	inf:	the last infile name in the part of input seperated by '|'.
			For exapmle,
			1. the input: "<<end <infile <<sp <infile2 cat | ..."
				in this case, inf = "infile2";
			2. the input: "<<end <infile <<sp cat | ..."
				in this case, inf = NULL; (becasue there is no infile)

	intype:	the last < or << in the part of input seperated by '|'.
			For exapmle, the input :"<<end <infile <<sp cat | ..."
			in this case, intype = TK_HDOC, becase it is the last one.
			But if there is no < or <<:
				if there is a pipe, then intype = TK_PIPE;
				if there is NO pipe, then intype = TK_NONE;
			the priority is(high to low) : redirection, pipe, none

	outype:	the last > or >> in the part of input seperated by '|';
			But if there is no > or >>:
				if there is a pipe, then intype = TK_PIPE;
				if there is NO pipe, then intype = TK_NONE;
			the priority is(high to low) : redirection, pipe, none

	ifnum:	the amount of input redirection '<';
	ofnum:	the amount of output redirection '>';
	herenum:	the amount of heredoc '<<';
	ct_in:	the index of infile dyadic array;
	ct_out:	the index of outfile dyadic array;
	ct_del:	the index of limiter dyadic array;
	ct_w:	the index of cmd dyadic array;
*/
typedef struct s_cmd
{
	char			**cmd;
	char			**infile;
	char			**limiter;
	char			**outfile;
	char			*of;
	char			*inf;
	t_token_type	intype;
	t_token_type	outype;
	int				ofnum;
	int				ifnum;
	int				herenum;
	int				word;
	int				ct_in;
	int				ct_out;
	int				ct_del;
	int				ct_w;
	int				prev_fd;
	struct s_list	*iolist;
	struct s_cmd	*next;
}	t_cmd;

#endif
