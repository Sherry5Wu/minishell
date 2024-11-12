/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 20:10:50 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/12 13:47:18 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	bubble_sort(char **env, int count)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - 1 - i)
		{
			if (env[j][0] > env[j + 1][0])
			{
				temp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

char	**sort_env(void)
{
	char	**env_copy;
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (ms()->env[count])
		count++;
	env_copy = malloc(count * sizeof(char *));
	while (i < count)
	{
		env_copy[i] = ms()->env[i];
		i++;
	}
	bubble_sort(env_copy, count);
	return (env_copy);
}

bool	ft_valid_character(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
	}
	return (true);
}

int	count_array_size(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
	}
	return (i);
}

void	add_env(char *str)
{
	int		i;
	int		j;
	char	**new_env;

	i = count_array_size(ms()->env);
	new_env = malloc((i + 2) * sizeof(char *));
	if (new_env == NULL)
		restart(1);
	j = -1;
	while (++j < i)
		new_env[j] = ft_strdup(ms()->env[j]);
	new_env[i] = ft_strdup(str);
	new_env[i + 1] = NULL;
	if (new_env[i] == NULL)
		restart(1);
	pp_ft_free_str(ms()->env);
	ms()->env = new_env;
}
