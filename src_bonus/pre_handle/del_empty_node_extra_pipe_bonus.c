/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_empty_node_extra_pipe_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 07:50:10 by jingwu            #+#    #+#             */
/*   Updated: 2024/11/11 13:53:55 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

/*
	@function
	Work with function delete_extra_pipes(), to delete extra pipes in the
	token list after local variable checking. This function is just delete
	the pipes which are at the beiginning of the list.
*/
static void	del_beginning_pipes(t_list **list)
{
	t_token	*current;
	t_list	*tmp;

	if (!list || !*list)
		return ;
	while (*list)
	{
		current = (t_token *)((*list)->content);
		if (current->tk_type == TK_PIPE)
		{
			tmp = (*list);
			(*list) = (*list)->next;
			del_node(tmp);
		}
		else
			return ;
	}
}

static void	delete_end_pipe(t_list *list)
{
	t_list	*end_node;

	if (!list || !list->next)
		return ;
	while (list && list->next && list->next->next)
		list = list->next;
	if (((t_token *)list->next->content)->tk_type == TK_PIPE)
	{
		end_node = list->next;
		list->next = NULL;
		del_node(end_node);
	}
}

/*
	@function
	After checking the local variables, in some conditions, the valid variable
	definations will be deleted. Then it might leave extra pipe token in the
	list, so we need to delete these extra pipes
	The node might be in three places:
	1. at the beginnings;
	2. in the middle;
	3. at the end;
*/
static void	delete_extra_pipes(t_list *list)
{
	t_token	*current;
	t_token	*next;
	t_list	*tmp;
	t_list	*newlist;

	if (!list)
		return ;
	newlist = list;
	while (newlist)
	{
		current = (t_token *)(newlist->content);
		if (newlist->next)
		{
			next = (t_token *)(newlist->next->content);
			if (current->tk_type == TK_PIPE && next->tk_type == TK_PIPE)
			{
				tmp = newlist->next;
				newlist->next = tmp->next;
				del_node(tmp);
				continue ;
			}
		}
		newlist = newlist->next;
	}
	delete_end_pipe(list);
}

static void	del_beginning_empty_str(t_list **list)
{
	t_token	*current;
	t_list	*tmp;

	if (!list || !*list)
		return ;
	while (*list)
	{
		current = (t_token *)((*list)->content);
		if (ft_strcmp(current->str, "") == 0)
		{
			tmp = (*list);
			(*list) = (*list)->next;
			del_node(tmp);
		}
		else
			return ;
	}
}

/*
	@function
	Before create cmd list, we need to delete the empty tokens and extra pipes
	that generated during pre-process.
	empty tokens:
	- input "$n | echo a", if there is no variable name is 'n', then it will
	  generate an empty token, after delete this empty, it leaves extra pipes;
	- input "n=2 | 1c=3 | a=b", because there is an invalid local variable
	  define in the input, in this case, in the pre-process
	  (are_all_def_loc_var()) will set the valid token n=2 and a=b to empty str.
*/
void	del_empty_node_extra_pipe(t_list **list)
{
	t_token	*token;
	t_list	*delete;
	t_list	*tmp;

	if (!list)
		return ;
	del_beginning_empty_str(list);
	tmp = *list;
	while (tmp && tmp->next)
	{
		token = (t_token *)(tmp->next->content);
		if (ft_strcmp(token->str, "") == 0)
		{
			delete = tmp->next;
			tmp->next = delete->next;
			del_node(delete);
			continue ;
		}
		tmp = tmp->next;
	}
	del_beginning_pipes(list);
	delete_extra_pipes(ms()->tokens);
}
