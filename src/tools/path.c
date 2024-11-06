/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:22:31 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/05 20:25:15 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if ((!(*s1) && *s2) || (*s1 && !*s2))
		return (*s1 - *s2);
	return (0);
}

static inline char	*pathincmd(char **shellcmd)
{
	if (!access(shellcmd[0], F_OK))
		return (ft_strdup(shellcmd[0]));
	else
		ex_error(shellcmd[0], NFILE, 127);
	return (NULL);
}

static inline char	*check_filename(char **filename, char **cmd)
{
	char	*path;
	char	*full_path;
	int		i;

	i = 0;
	while (filename[i])
	{
		path = ft_strjoin(filename[i++], "/");
		if (!path)
			return (0);
		full_path = ft_strjoin(path, cmd[0]);
		free(path);
		if (!full_path)
			return (0);
		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
		{
			pp_free(filename);
			return (full_path);
		}
		free(full_path);
	}
	pp_free(filename);
	return (0);
}

char	*findvalidcmd(char **shellcmd)
{
	char	**filename;

	if (ft_strchr(shellcmd[0], '/'))
		return (pathincmd(shellcmd));
	if (!ms()->path)
		ex_error(shellcmd[0], NFILE, 127);
	filename = ft_split(ms()->path + 5, ':');
	if (!filename)
		return (NULL);
	return (check_filename(filename, shellcmd));
}
