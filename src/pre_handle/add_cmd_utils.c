/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 08:21:42 by jingwu            #+#    #+#             */
/*   Updated: 2024/11/05 11:30:28 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	The function will count the amount of <, >, >> and <<.
	TK_type between 6 to 10 are : 	TK_SINGLE_QT, TK_DOUBLE_QT, TK_WORD,
	TK_LOC_V, TK_ENV_V.
*/
void	count(t_cmd **cmd, t_list *tk_lt, int start, int end)
{
	t_token	*token;

	while (tk_lt)
	{
		token = tk_lt->content;
		if (token->idx >= start && token->idx <= end)
		{
			if (token->tk_type == TK_IN_RE)
				(*cmd)->ifnum++;
			else if (token->tk_type == TK_OUT_RE || token->tk_type == TK_APPEND)
				(*cmd)->ofnum++;
			else if (token->tk_type == TK_HDOC)
				(*cmd)->herenum++;
			else if (token->tk_type >= 6 && token->tk_type <= 10)
				(*cmd)->word++;
		}
		if (token->idx > end)
			break ;
		tk_lt = tk_lt->next;
	}
}

/*
	Allocate memory for cmd, infile, outfile, limiter dyadic array.
*/
bool	allocate_mem(t_cmd **cmd)
{
	if ((*cmd)->ifnum > 0)
	{
		(*cmd)->infile = ft_calloc(((*cmd)->ifnum + 1), sizeof(char *));
		if (!(*cmd)->infile)
			return (false);
	}
	if ((*cmd)->ofnum > 0)
	{
		(*cmd)->outfile = ft_calloc(((*cmd)->ofnum + 1), sizeof(char *));
		if (!(*cmd)->outfile)
			return (false);
	}
	if ((*cmd)->word > 0)
	{
		(*cmd)->cmd = ft_calloc(((*cmd)->word + 1), sizeof(char *));
		if (!(*cmd)->cmd)
			return (false);
	}
	if ((*cmd)->herenum > 0)
	{
		(*cmd)->limiter = ft_calloc(((*cmd)->herenum + 1), sizeof(char *));
		if (!(*cmd)->limiter)
			return (false);
	}
	return (true);
}

/*
	@function
	In some condition to change a cmd's intypt to TK_NONE;
	for "ls -l >in | cat", for the second part cmd "cat", the intype should
	be TK_NONE, not TK_PIPE.
	The rule is as long the former cmd has ">" or ">>" then the next cmd's
	intype is TK_NONE.
*/
void	recorrect_cmd_intype(t_cmd *list)
{
	bool	flag;

	flag = false;
	if (!list)
		return ;
	while (list)
	{
		if (flag == true)
			list->intype = TK_NONE;
		if (list->ct_out > 0)
			flag = true;
		else
			flag = false;
		list = list->next;
	}
}
