/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:51:58 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/12 13:47:18 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cm(t_cmd *head)
{
	int		count;
	t_cmd	*current;

	current = head;
	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	*ft_strndup(char *src, int size)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(sizeof(char) * (size + 1));
	if (dest == NULL)
		return (NULL);
	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

pid_t	type_outpipe(t_cmd *cm, int *prev_fd)
{
	pid_t	pipeid;

	if (pipe(ms()->fd) == -1)
		ex_error("Pipe", PIPE, EXIT_FAILURE);
	pipeid = exe_pipe(cm);
	close(ms()->fd[1]);
	if (*prev_fd != -1)
		close(*prev_fd);
	*prev_fd = ms()->fd[0];
	return (pipeid);
}

t_ms	*ms(void)
{
	static t_ms	ms;

	return (&ms);
}

char	*prompt(void)
{
	char	*str;
	char	*str2;

	str = ft_strjoin("minishell:", ms()->cwd);
	if (!str)
		return (NULL);
	str2 = ft_strjoin(str, "$ ");
	if (!str2)
	{
		ft_free_str(str);
		return (NULL);
	}
	ft_free_str(str);
	return (str2);
}
