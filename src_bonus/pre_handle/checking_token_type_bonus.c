/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_token_type_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:47:08 by jingwu            #+#    #+#             */
/*   Updated: 2024/11/11 13:53:52 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

bool	is_pipe(t_token *token)
{
	if (!token)
		return (false);
	if (token->tk_type == TK_PIPE)
		return (true);
	return (false);
}

bool	is_dir(t_token *token)
{
	if (!token)
		return (false);
	if (token->tk_type == TK_IN_RE || token->tk_type == TK_OUT_RE
		|| token->tk_type == TK_HDOC || token->tk_type == TK_APPEND)
		return (true);
	return (false);
}

bool	is_dir_or_pipe(t_token *token)
{
	if (!token)
		return (false);
	if (is_pipe(token) || is_dir(token))
		return (true);
	return (false);
}

/*
	Here the seperators contain:|, <,>,',", space, \0,
*/
bool	is_seperator(char c)
{
	char	*sep;

	sep = "|<>\'\"\0 ";
	if (!ft_strchr(sep, c))
		return (false);
	return (true);
}
