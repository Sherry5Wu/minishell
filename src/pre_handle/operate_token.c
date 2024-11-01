/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:28:56 by jingwu            #+#    #+#             */
/*   Updated: 2024/11/01 09:33:29 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Generate a new node for lexer_list.
*/
t_token	*new_token(char *str, t_token_type tk_type, bool merge)
{
	t_token	*node;

	node = ft_calloc(1, sizeof(t_token));
	if (!node)
		return (NULL);
	node->str = str;
	node->tk_type = tk_type;
	node->merge = merge;
	node->idx = -1;
	return (node);
}

/*
	Add a new node to the token list;
*/
int	add_token(char *str, t_token_type token, bool merge)
{
	t_token		*node;

	if (!str)
		return (false);
	node = new_token(str, token, merge);
	if (!node)
		return (-1);
	ft_lstadd_back(&ms()->tokens, (ft_lstnew(node)));
	return (ft_strlen(str));
}

/*
	@Why I need this function?
	Becasue if I don't use it, then if I want to get the value of a t_token
	type data, I need write "((t_token *)(ms() ->tokens))->str", it is too
	looooooong.

	psn == RESET
		SET the tk_list to pointer to the head of list tokens;
	psn == NEXT
		MOVE the pointer to the next node;
	psn == CURRENT
		RETURN the content(t_token type) of the current node;
	psn == PREVIEW
		RETURN the content (t_token type) of the next node;
*/
t_token	*tk_list_manager(t_list_position psn)
{
	static t_list	*tk_list = NULL;

	if (psn == RESET)
		tk_list = ms()->tokens;
	else if (psn == NEXT)
		tk_list = tk_list->next;
	else if (psn == CUR_CNT && tk_list)
		return ((t_token *)(tk_list->content));
	else if (psn == NEXT_CNT && tk_list->next)
		return ((t_token *)(tk_list->next->content));
	return (NULL);
}

void	delete_token(t_token *token)
{
	if (!token)
		return ;
	if (token->str)
		free(token->str);
	token->str = NULL;
	if (token->arg)
		free(token->arg);
	token->arg = NULL;
	token->tk_type = -1;
	token->idx = -1;
	token->merge = 0;
	ft_free_str(token);
	token = NULL;
}

void	del_node(t_list *node)
{
	ft_lstdelone(node, (void *)delete_token);
	node = NULL;
}
