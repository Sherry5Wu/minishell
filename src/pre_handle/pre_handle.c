/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:48:19 by jingwu            #+#    #+#             */
/*   Updated: 2024/09/25 14:18:45 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

bool	pre_handle(void)
{
	if (!check_quote()) // it will check if the input is quoted correctly
		return (print_error(UNQUOTED));
	if (!lexer())
		return (print_error(ADD_LEXER_FAILED));
	if (!parsing())
		return (false); // should return an error message here
	
	
	
	expander();
	if (check_all_local()) // what's this for?????
		return (false); // should return an error message here
	return (true);
}
