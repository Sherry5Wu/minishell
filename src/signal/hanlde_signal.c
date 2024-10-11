/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hanlde_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:18:58 by jingwu            #+#    #+#             */
/*   Updated: 2024/10/11 10:38:01 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
	@function
	When receive a SIGINT, it will display a new prompt on a new line.

	@steps
	1. replaces the current input line with an empty string,
	   essentially clearing the user’s input.
	2. Prints a newline character, usually to format the output
	   nicely and move the cursor to the next line.
	3. Informs the readline library that the cursor has moved
	   to a new line, preparing for new input.
	4. Redisplays the input line and updates the terminal’s display.
*/
void	handle_sigint(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		restart(true);
		(ms()->exit) = 130;
	}
}
