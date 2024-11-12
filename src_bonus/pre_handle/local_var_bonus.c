/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_var_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:05:21 by jingwu            #+#    #+#             */
/*   Updated: 2024/11/11 13:54:05 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

/*
	@function
	work with checking_list_token_types() to return the type.
*/
static int	return_value(int loc_v, int pipe, int others)
{
	if (loc_v == 0)
		return (4);
	else if (others > 0)
		return (3);
	else if (pipe > 0)
		return (2);
	else
		return (1);
}

/*
	@function
	Checking the passed list's token types.

	@return
		1: only contain TK_LOC_V;
		2: contain TK_LOC_V and TK_PIPE
		3: contain at least one other token type except TK_LOC_V and TK_PIPE;
		4: there is no TK_LOC_V;
*/
static int	checking_list_token_types(t_list *list)
{
	t_token	*token;
	int		loc_v;
	int		pipe;
	int		others;

	loc_v = 0;
	pipe = 0;
	others = 0;
	if (!list)
		return (4);
	while (list)
	{
		token = (t_token *)list->content;
		if (token->tk_type != TK_LOC_V && token->tk_type != TK_PIPE)
			others++;
		else if (token->tk_type == TK_PIPE)
			pipe++;
		else if (token->tk_type == TK_LOC_V)
			loc_v++;
		list = list->next;
	}
	return (return_value(loc_v, pipe, others));
}

/*
	@function
	While loop the token list, if found one TK_LOC_V type token is not valid
	defination variable, then return true. If every TK_LOC_V type token is
	valid defination, then return false.

	@return
	true: there is at least one invalid variable defination
	false: there is NO invalid variable defination
*/
static bool	is_there_invalid_defination(t_list *list)
{
	t_token	*token;

	if (!list)
		return (false);
	while (list)
	{
		token = (t_token *)list->content;
		if (token->tk_type == TK_LOC_V && is_defining_var(token->str) == false)
			return (true);
		list = list->next;
	}
	return (false);
}

/*
	@function
	Working with are_all_def_loc_var() function, set the token str to empty
	when it fullfills certain conditions.
*/
static void	set_token_str_empty(t_list *list)
{
	t_token	*token;

	while (list)
	{
		token = (t_token *)(list->content);
		if (token->tk_type == TK_LOC_V && is_defining_var(token->str) == true)
		{
			ft_free_str(token->str);
			token->str = ft_strdup("");
		}
		list = list->next;
	}
}

/*
	type:
		1: only contain TK_LOC_V;
		2: contain TK_LOC_V and TK_PIPE
		3: contain at least one other token type except TK_LOC_V and TK_PIPE;
		4: there is no TK_LOC_V;

	The different input cases and their actions:
	type=1	1: name=123 a=3		--> saving variables, don't go to execution
	type=1	2: name=23 1a=3		--> don't save any variable,
									empty "name=123", go to execution
	type=2	3: name=123 | a=3	--> don't save any variable,
									don't go to execution
	type=2	4: name=123 | 1a=3	--> don't save any variable,
									empty "name=123", go to execution
	type=3	5: name=123 | echo a	--> don't save any variable,
									empty "name=123", go to execution
	type=3	6: name=123 | 1name=123 | echo a	--> don't save any variable,
											empty "name=123", go to execution
	type=4	7: echo a | ls -l	--> don't need to do anything, go to execution

	Why we set valid defination str to empty in some conditions?
	In subsequent process, we will delete these empty tokens. Becasue other
	process will generate empty token too. So we combine the delete together.

	Logic summary:
	1. As long there is an INVAILD variable defination in the input or the
	   type = 3, then:
		- DON'T save any valid variable
		- Delete all the valid variable definations
		- Go to execution
	2. if type = 1, add variables to the local variable list, restart the
	   minishell;
	3. if type = 2, restart the minishell
*/
bool	are_all_def_loc_var(void)
{
	t_list	*tmp;
	t_token	*token;
	int		type;

	type = checking_list_token_types(ms()->tokens);
	if ((type == 1 || type == 2)
		&& is_there_invalid_defination(ms()->tokens) == false)
	{
		if (type == 1)
		{
			tmp = ms()->tokens;
			while (tmp)
			{
				token = (t_token *)(tmp->content);
				add_node_to_list(&(ms()->local_var), token->str);
				tmp = tmp->next;
			}
		}
		return (true);
	}
	else if (is_there_invalid_defination(ms()->tokens) == true || type == 3)
		set_token_str_empty(ms()->tokens);
	return (false);
}
