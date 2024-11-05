/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:10:09 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/02 15:10:11 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./minishell.h"

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

	count = 0;
	while (ms()->env[count])
		count++;
	env_copy = malloc(count * sizeof(char *));
	for (int i = 0; i < count; i++)
	{
		env_copy[i] = ms()->env[i];
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

// void	update_env(int	i, char	*str)
// {
// 	free(ms()->env[i]);
// 	ms()->env[i] = ft_strdup(str);
// }

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
/*
	add a new env to ms()->env.
*/
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
	pp_free(ms()->env);
	ms()->env = new_env;
}

void	update_or_add(char *str)
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
		// in add_node_to_list() it will check if the env exist or not
	free(name);
}

char	*lastequal(char *str)
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

/*
	1. input: export a-
		output: bash: export: `a-': not a valid identifier
	2. input: export a 1
		output: bash: export: `1': not a valid identifier
	3. input: export aa
		output:(nothing, restart shell, don't add env)
	4. input: export a=123
		output: (nothing, restart shell, add a=123 to env and env_list)
	5. input: export 1 2
		output: bash: export: `1': not a valid identifier
				bash: export: `2': not a valid identifier
*/
int	ft_export(char **cmd)
{
	int		i;
	int		status;
	char	*result;

	i = 1;
	status = 1;
	if (!cmd[1])
		return (print_sorted_env());
	while (cmd[i])
	{
		if (ft_isalpha(cmd[i][0]) || cmd[i][0] == '_')
		{
			if (ft_strchr(cmd[i], '='))
			{
				result = lastequal(cmd[i]);
					// add for free the memory that created in lastequal().
				if (!ft_valid_character(result))
					status = export_err(cmd[i]);
				else
					update_or_add(cmd[i]);
				ft_free_str(result);
					// add for free the memory that created in lastequal().
			}
			else if (!ft_valid_character(cmd[i]))
				status = export_err(cmd[i]);
		}
		else
			status = export_err(cmd[i]);
		i++;
	}
	if (status)
		ms()->exit = 0;
	return (1);
}
