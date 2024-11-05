/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restart.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:08:50 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/05 13:25:34 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	print_sig_info(void)
{
	if (ms()->exit == 131)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	else if (ms()->exit == 139)
		ft_putstr_fd("Segmentation fault (core dumped)\n", STDERR_FILENO);
	else if (ms()->exit == 130)
		ft_putstr_fd("\n", STDERR_FILENO);
}

void free_list(t_list *head)
{
	t_list *temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->content);
		free(temp);
	}
}
void restart(int ex)
{

	if (ms()->prompt)
		free(ms()->prompt);
	if(ms()->input)
		free(ms()->input);
	ms()->fd[0] = -1;
	ms()->fd[1] = -1;
	ms()->in_fd = STDIN_FILENO;
	ms()->out_fd = STDOUT_FILENO;
//	free_token_list();
	ft_lstclear((&ms()->tokens), (void (*)(void *))delete_token);
	free_cmd_list();
	print_sig_info();
	if(ex)
	{
		free(ms()->cwd);
		pp_free(ms()->env);
		free_local_var_list();
		ft_lstclear((&ms()->env_list), (void (*)(void *))free_env);
		exit(ms()->exit);
	}
}

void	close_inout()
{

	if (ms()->in_fd != 0 && ms()->in_fd != -1)
		close(ms()->in_fd);
	if (ms()->out_fd != 1  && ms()->out_fd != -1)
		close(ms()->out_fd);
}

void	close_all(int	prev_fd)
{
	unlink("here_doc");
	if (prev_fd != -1)
		close(prev_fd);
	close_inout();
}
