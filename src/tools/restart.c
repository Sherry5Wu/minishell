/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restart.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:08:50 by yzheng            #+#    #+#             */
/*   Updated: 2024/10/23 12:06:49 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./minishell.h"
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
	free_token_list();
	free_cmd_list();
	// printf ("In restart:\n");// for testing!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	// print_env("PWD", 3); // for testing!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	// print_env("OLDPWD", 6); // for testing!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1

	if(ex)
	{
		free(ms()->cwd);
		pp_free(ms()->env);
		free_local_var_list();
//		printf("inside_exit, exit_code=%d\n", ms()->exit);//for testing!!!!!
		exit(ms()->exit);
	}
}

void	close_inout()
{
	if (ms()->in_fd != 0)
		close(ms()->in_fd);
	if (ms()->out_fd != 1)
		close(ms()->out_fd);
}

void	close_all(int	prev_fd)
{
	unlink("here_doc");
	if (prev_fd != -1)
		close(prev_fd);
	close_inout();
}
