/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 09:04:56 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/12 13:47:18 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_infile(t_cmd *cm)
{
	int	i;
	int	fd;

	fd = 0;
	i = 0;
	if (cm->ifnum > 1)
	{
		while (i < cm->ifnum - 1)
		{
			fd = open(cm->infile[i++], O_RDONLY, 0444);
			if (fd == -1)
				open_error(cm->infile[--i]);
			close(fd);
		}
	}
	if (ms()->in_fd == -1)
		exit(ms()->exit);
	if (cm->intype == TK_HDOC)
		cm->ifnum++;
}

char	*replace_first_substring(char *str, char *old_sub, char *new_sub)
{
	char	*result;
	char	*pos;
	int		new_len;
	int		old_len;

	new_len = ft_strlen(new_sub);
	old_len = ft_strlen(old_sub);
	pos = ft_strnstr(str, old_sub, ft_strlen(str));
	result = (char *)malloc(ft_strlen(str) - old_len + new_len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, str, pos - str + 1);
	result[pos - str] = '\0';
	ft_strlcat(result, new_sub, ft_strlen(result) + new_len + 1);
	ft_strlcat(result, pos + old_len, ft_strlen(result) + ft_strlen(pos
			+ old_len) + 1);
	ft_free_str(old_sub);
	return (result);
}

char	*findpath(char **env)
{
	int	i;

	i = 0;
	while (env[i] && !ft_strnstr(env[i], "PATH", 4))
		i++;
	return (env[i]);
}

int	print_sorted_env(void)
{
	int		i;
	int		j;
	char	**envsort;

	i = 0;
	j = 0;
	envsort = sort_env();
	while (ms()->env[i])
	{
		j = 0;
		printf("declare -x ");
		while (envsort[i][j] != '=')
			printf("%c", envsort[i][j++]);
		j++;
		printf("=\"");
		while (envsort[i][j])
			printf("%c", envsort[i][j++]);
		printf("\"\n");
		i++;
	}
	ft_free_str(envsort);
	return (1);
}

void	free_env(t_env *env)
{
	ft_free_str(env->name);
	ft_free_str(env->value);
	ft_free_str(env);
	env = NULL;
}
