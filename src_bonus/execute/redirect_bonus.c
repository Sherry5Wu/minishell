/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:20:57 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/11 13:53:39 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	set_errors(char *message)
{
	if (!access(message, F_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		if (message)
			ft_putstr_fd(message, 2);
		ft_putstr_fd(" : Permission denied", 2);
		ms()->exit = 1;
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		if (message)
			ft_putstr_fd(message, 2);
		ft_putstr_fd(" : No such file or directory", 2);
		ms()->exit = 1;
	}
	ft_putchar_fd('\n', 2);
	return (0);
}

static int	check_files(t_list *cm)
{
	int	fd;

	fd = 0;
	if (ft_atoi(((t_env *)(cm)->content)->name) == 2)
	{
		fd = open(((t_env *)(cm)->content)->value, O_RDONLY, 0444);
		if (fd == -1)
			return (set_errors(((t_env *)(cm)->content)->value));
	}
	else if (ft_atoi(((t_env *)(cm)->content)->name) == 3)
	{
		fd = open(((t_env *)(cm)->content)->value, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (fd == -1)
			return (set_errors(((t_env *)(cm)->content)->value));
	}
	else if (ft_atoi(((t_env *)(cm)->content)->name) == 5)
	{
		fd = open(((t_env *)(cm)->content)->value,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (set_errors(((t_env *)(cm)->content)->value));
	}
	close(fd);
	return (1);
}

static int	set_fd_in(t_cmd *cm)
{
	t_list	*temp;

	temp = cm->iolist;
	if (ms()->in_fd == -1)
		ms()->in_fd = STDIN_FILENO;
	while (temp)
	{
		if (!check_files(temp))
			break ;
		temp = temp->next;
	}
	if (cm->intype == TK_IN_RE)
		(ms()->in_fd) = open(cm->inf, O_RDONLY, 0444);
	if (cm->intype == TK_PIPE)
		(ms()->in_fd) = ms()->fd[0];
	if (ms()->in_fd == -1)
	{
		close_inout();
		return (1);
	}
	return (0);
}

static int	set_fd_out(t_cmd *cm)
{
	if (cm->outype == TK_OUT_RE)
		(ms()->out_fd) = open(cm->of, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (cm->outype == TK_APPEND)
		(ms()->out_fd) = open(cm->of, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (cm->outype == TK_NONE)
		(ms()->out_fd) = STDOUT_FILENO;
	if (ms()->out_fd == -1)
	{
		close_inout();
		return (1);
	}
	return (0);
}

int	set_fd(t_cmd *cm)
{
	int	i;
	int	ofd;

	i = 0;
	ofd = 0;
	if (set_fd_in(cm))
		return (1);
	while (i < cm->ofnum)
	{
		ofd = open(cm->outfile[i++], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (ofd == -1)
		{
			close_inout();
			return (0);
		}
		close(ofd);
	}
	if (set_fd_out(cm))
		return (1);
	return (1);
}
