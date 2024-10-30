/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 08:14:19 by jingwu            #+#    #+#             */
/*   Updated: 2024/10/29 17:00:04 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Document's requirements:
	ctrl-C displays a new prompt on a new line.
	ctrl-D exits the shell. Sending EOF signal,
	ctrl-\ does nothing.
*/

/*
	@What the function does?
	To listening SIGINT (ctrl-C) and SIGQUIT(ctrl-\).

	@action
	When receive SIGINT, we call handle_sigint();
	When receive SIGQUIT, we ignore it(SIG_IGN);
*/
void	signal_default(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	if(ms()->heredoc_count == -1)
	{
		printf("minishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n",ms()->lines,ms()->cmds->limiter[--ms()->limiter_count]);
		ms()->heredoc_count = 0;
	}
}

void	signal_heredoc(void)
{
	signal(SIGINT, handle_heredoc);
	signal(SIGQUIT, SIG_IGN);

}

void	signal_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signal_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
