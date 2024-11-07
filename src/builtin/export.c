/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:10:09 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/07 11:19:45 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	update_or_add(char *str)
{
	int		i;
	char	*name;
	int		size;
	t_list	*tmp;

	tmp = ms()->env_list;
	size = 0;
	while (str[size] != '=')
		size++;
	name = ft_strndup(str, size);
	i = 0;
	while (ms()->env[i] && !ft_strnstr(ms()->env[i], name, size))
		i++;
	if (!ms()->env[i])
		add_env(str);
	else
	{
		free(ms()->env[i]);
		ms()->env[i] = ft_strdup(str);
	}
	add_node_to_list(&ms()->env_list, str);
	free(name);
}

static char	*lastequal(char *str)
{
	int		length;
	char	*last_equal;
	char	*result;

	last_equal = ft_strrchr(str, '=');
	if (last_equal != NULL)
	{
		length = last_equal - str;
		result = malloc(sizeof(char) * (length + 1));
		if (result == NULL)
		{
			perror("Failed to allocate memory");
			return (NULL);
		}
		strncpy(result, str, length);
		result[length] = '\0';
	}
	else
		return (NULL);
	return (result);
}

static int	handle_export_argument(char *arg)
{
	char	*result;
	int		status;

	status = 1;
	if (ft_isalpha(arg[0]) || arg[0] == '_')
	{
		if (ft_strchr(arg, '='))
		{
			result = lastequal(arg);
			if (!ft_valid_character(result))
				status = export_err(arg);
			else
				update_or_add(arg);
			ft_free_str(result);
		}
		else if (!ft_valid_character(arg))
			status = export_err(arg);
	}
	else
		status = export_err(arg);
	return (status);
}

int	ft_export(char **cmd)
{
	int	i;
	int	status;

	i = 1;
	status = 1;
	if (!cmd[1])
		return (print_sorted_env());
	while (cmd[i])
	{
		if (!handle_export_argument(cmd[i]))
			status = 0;
		i++;
	}
	if (status)
		ms()->exit = 0;
	return (1);
}
