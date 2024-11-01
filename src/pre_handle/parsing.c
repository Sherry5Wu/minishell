/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:24:17 by jingwu            #+#    #+#             */
/*   Updated: 2024/10/24 08:55:07 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	TK_type between 6 to 10 are : 	TK_SINGLE_QT, TK_DOUBLE_QT, TK_WORD,
	TK_LOC_V, TK_ENV_V.
*/
static void	action(t_token *token, t_cmd **cmd, t_list *tmp, int end)
{
	if (is_dir(token))
		process_re(cmd, tmp);
	else if (token->tk_type >= 6 && token->tk_type <= 10)
		(*cmd)->cmd[(*cmd)->ct_w++] = ft_strdup(token->str);
	if (token->idx == end && token->tk_type == TK_PIPE
		&& (*cmd)->outype == TK_NONE)
		(*cmd)->outype = TK_PIPE;
}

static t_cmd	*new_cmd(int start, int end)
{
	t_list	*tmp;
	t_token	*token;
	t_cmd	*cmd_nd;

	tmp = ms()->tokens;
	cmd_nd = ft_calloc(1, sizeof(t_cmd));
	count(&cmd_nd, tmp, start, end);
	if (!allocate_mem(&cmd_nd))
		return (NULL);
	cmd_nd->intype = TK_PIPE;
	cmd_nd->outype = TK_NONE;
	if (start == 0)
		cmd_nd->intype = TK_NONE;
	while (tmp)
	{
		token = tmp->content;
		if (token->idx >= start && token->idx <= end)
			action(token, &cmd_nd, tmp, end);
		if (token->idx > end)
			break ;
		tmp = tmp->next;
	}
	cmd_nd->next = NULL;
	return (cmd_nd);
}

static bool	add_cmd(t_cmd *new)
{
	t_cmd	*tmp;

	if (!new)
		return (false);
	if (!(ms()->cmds))
		ms()->cmds = new;
	else
	{
		tmp = ms()->cmds;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (true);
}

/*
	This function will group tokens seperated by '|', then add them into
	cmd_list;
*/
bool	parsing(void)
{
	t_list	*tmp;
	t_token	*token;
	int		i;
	bool	sign;

	if (!ms()->tokens)
		return (false);
	i = 0;
	sign = true;
	tmp = ms()->tokens;
	while (tmp)
	{
		token = (t_token *)(tmp->content);
		if (token->tk_type == TK_PIPE && tmp->next)
		{
			sign = add_cmd(new_cmd(i, token->idx));
			i = token->idx + 1;
		}
		if (!tmp->next)
			sign = add_cmd(new_cmd(i, ((t_token *)tmp->content)->idx));
		if (!sign)
			return (print_error(ADD_CMD_ERR, 1));
		tmp = tmp->next;
	}
	return (true);
}
