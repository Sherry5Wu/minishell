/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restart_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:08:50 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/12 13:47:18 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	print_sig_info(void)
{
	if (ms()->exit == 131)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	else if (ms()->exit == 139)
		ft_putstr_fd("Segmentation fault (core dumped)\n", STDERR_FILENO);
	else if (ms()->exit == 130)
		ft_putstr_fd("\n", STDERR_FILENO);
}

void	restart(int ex)
{
	if (ms()->prompt)
		ft_free_str(ms()->prompt);
	if (ms()->input)
		ft_free_str(ms()->input);
	ms()->fd[0] = -1;
	ms()->fd[1] = -1;
	ms()->in_fd = STDIN_FILENO;
	ms()->out_fd = STDOUT_FILENO;
	ft_lstclear((&ms()->tokens), (void (*)(void *))delete_token);
	free_cmd_list();
	if (!ex)
		print_sig_info();
	if (ex)
	{
		ft_free_str(ms()->cwd);
		pp_ft_free_str(ms()->env);
		free_local_var_list();
		ft_lstclear((&ms()->env_list), (void (*)(void *))free_env);
		exit(ms()->exit);
	}
}

void	close_inout(void)
{
	if (ms()->in_fd != 0 && ms()->in_fd != -1)
		close(ms()->in_fd);
	if (ms()->out_fd != 1 && ms()->out_fd != -1)
		close(ms()->out_fd);
}

void	close_all(int prev_fd)
{
	unlink("here_doc");
	if (prev_fd != -1)
		close(prev_fd);
	close_inout();
}
