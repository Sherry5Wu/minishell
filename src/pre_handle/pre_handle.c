/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:48:19 by jingwu            #+#    #+#             */
/*   Updated: 2024/10/24 09:47:43 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	merge(t_list *list)
{
	t_token	*cur;
	t_token	*next;
	char	*tmp;
	t_list	*delete;

	while (list)
	{
		cur = list->content;
		if (!(list->next))
			return ;
		if (!cur->merge)
		{
			list = list->next;
			continue ;
		}
		next = (list->next)->content;
		tmp = cur->str;
		cur->str = ft_strjoin(cur->str, next->str);
		free(tmp);
		if (!next->merge)
			cur->merge = next->merge;
		delete = list->next;
		list->next = list->next->next;
		del_node(delete);
	}
}

static void	restruct_token(void)
{
	t_list	*tmp;
	t_token	*cur_tk;
	t_list	*delete;

	tmp = ms()->tokens;
	while (tmp)
	{
		cur_tk = (t_token *)(tmp->content);
		if (!tmp->next)
			break ;
		if (is_dir(cur_tk))
		{
			cur_tk->arg = ft_strdup(((t_token *)((tmp->next)->content))->str);
			delete = tmp->next;
			if (!(tmp->next)->next)
			{
				tmp->next = NULL;
				break ;
			}
			tmp->next = (tmp->next)->next;
			del_node(delete);
		}
		tmp = tmp->next;
	}
}

static void	assign_token_index(void)
{
	t_list	*list;
	t_token	*token;
	int		i;

	list = ms()->tokens;
	i = 0;
	while (list)
	{
		token = (t_token *)(list->content);
		token->idx = i++;
		list = list->next;
	}
}

/*
	@function
	Change the environment variable's type to TK_ENV_V, and local variable's
	type to TK_LOC_V. Before theirs types are TK_WORD.
*/
static void	add_variable_type(t_list *list)
{
	t_token	*token;
	t_token	*next;

	if (!list)
		return ;
	while (list)
	{
		token = (t_token *)(list->content);
		if (ft_strcmp(token->str, "export") == 0 && list->next)
		{
			next = (t_token *)(list->next->content);
			if (ft_strchr(next->str, '='))
				next->tk_type = TK_ENV_V;
		}
		if (ft_strchr(token->str, '=') && token->tk_type != TK_ENV_V)
			token->tk_type = TK_LOC_V;
		list = list->next;
	}
}

bool	pre_handle(void)
{
	if (!check_quote())
		return (false);
	if (!lexer())
		return (false);
	if (!check_syntax())
		return (false);
	merge(ms()->tokens);
	restruct_token();
	expander();
	add_variable_type(ms()->tokens);
	if (are_all_def_loc_var() == true)
		return (false);
	del_empty_node_extra_pipe(&ms()->tokens);
	assign_token_index();
	if (!parsing())
		return (false);
	recorrect_cmd_intype(ms()->cmds);
	return (true);
}
