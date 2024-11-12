/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 20:12:44 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/12 13:47:18 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list	*cur;
	size_t	len;

	if (begin_list == NULL || *begin_list == NULL)
		return ;
	cur = *begin_list;
	len = ft_strlen(data_ref);
	if (len == ft_strlen(((t_env *)cur->content)->name)
		&& cmp(((t_env *)cur->content)->name, data_ref, len) == 0)
	{
		*begin_list = cur->next;
		ft_lstdelone(cur, (void (*)(void *))free_env);
		ft_list_remove_if(begin_list, data_ref, cmp);
	}
	else
	{
		cur = *begin_list;
		ft_list_remove_if(&cur->next, data_ref, cmp);
	}
}

static int	find_env(char *name)
{
	int	i;

	i = 0;
	while (ms()->env[i] && !ft_strnstr(ms()->env[i], name, ft_strlen(name)))
		i++;
	if (!ms()->env[i])
		return (-1);
	return (i);
}

static void	remove_env(int index)
{
	int	i;

	if (index == -1)
		return ;
	i = index;
	ft_free_str(ms()->env[index]);
	while (ms()->env[i])
	{
		ms()->env[i] = ms()->env[i + 1];
		i++;
	}
	ms()->env[i] = NULL;
}

int	ft_unset(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[++i])
	{
		ft_list_remove_if(&ms()->env_list, cmd[i], ft_strncmp);
		remove_env(find_env(cmd[i]));
	}
	ms()->exit = 0;
	return (1);
}
