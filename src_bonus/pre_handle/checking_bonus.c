/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:55:19 by jingwu            #+#    #+#             */
/*   Updated: 2024/11/11 13:53:48 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

/*
	@param
	flag:
		false: unclosed quote;
		true: closed quote;
*/
bool	check_quote(void)
{
	int		i;
	char	quote;
	bool	flag;

	i = 0;
	flag = true;
	while (ms()->input[i])
	{
		if (flag && ft_strchr("\"\'", ms()->input[i]))
		{
			quote = ms()->input[i];
			flag = false;
		}
		else if (!flag && ms()->input[i] == quote)
			flag = true;
		i++;
	}
	if (!flag)
		return (print_error(UNQUOTED, 1));
	return (true);
}

/*
	@What condistions count as an error?
	1. the input starts with '|';
	2. the input end with <, >, << or >> or next them is antoher meta_char.
	   For exmample:
	   	input:	echo "Do you like minishell?" <
	   	input:	echo "Yes I like it!" < >
	3. the input end with '|' or 2 pipes together
	   For example:
	   	input:	echo "Another happy day" |
		input:	echo "true" | wc -l | | echo error
*/
bool	check_syntax(void)
{
	t_token	*next_tk;

	tk_list_manager(RESET);
	if (is_pipe(tk_list_manager(CUR_CNT)))
		return (print_error(PIPE_STX_ERR, 1));
	while (tk_list_manager(CUR_CNT))
	{
		next_tk = tk_list_manager(NEXT_CNT);
		if (is_dir(tk_list_manager(CUR_CNT))
			&& (!next_tk || is_dir_or_pipe(tk_list_manager(NEXT_CNT))))
			return (stx_error(next_tk));
		if (is_pipe(tk_list_manager(CUR_CNT)))
		{
			if (!next_tk || is_pipe(tk_list_manager(NEXT_CNT)))
				return (print_error(PIPE_STX_ERR, 1));
		}
		tk_list_manager(NEXT);
	}
	return (true);
}

bool	check_mergerable(char *matcher, char *str, int index)
{
	char	*meta_char;
	char	*quote;
	char	*special;

	meta_char = "<>'\"| ";
	quote = "'\"";
	special = "<>| ";
	if (!str[index])
		return (false);
	if (!ft_strcmp(meta_char, matcher) && ft_strchr(quote, str[index]))
		return (true);
	if (ft_strchr(quote, matcher[0]) && !ft_strchr(special, str[index + 1]))
		return (true);
	return (false);
}
