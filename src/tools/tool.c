/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 09:04:56 by yzheng            #+#    #+#             */
/*   Updated: 2024/10/04 11:39:59 by jingwu           ###   ########.fr       */
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
		while(i < cm->ifnum - 1)
		{
			fd = open(cm->infile[i++], O_RDONLY , 0444);
			if (fd == -1)
				open_error(cm->infile[--i]);
			close(fd);
		}
	}
}

void	pp_free(char **fly)
{
	int	j;

	j = 0;
	while (fly[j])
		free(fly[j++]);
	free(fly);
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

void	set_fd(t_cmd *cm)
{
	if (cm->intype == TK_IN_RE)
		(ms()->in_fd) = open(cm->inf, O_RDONLY, 0444);
	if (cm->intype == TK_PIPE)
		(ms()->in_fd) = ms()->fd[0];
	if (ms()->in_fd == -1)
		open_error(cm->inf);
	else if (cm->outype  == TK_OUT_RE)
		(ms()->out_fd) = open(cm->of, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (cm->outype == TK_APPEND)
		(ms()->out_fd) = open(cm->of, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (cm->outype == TK_NONE)
		(ms()->out_fd) = STDOUT_FILENO;
	if (ms()->out_fd == -1)
		open_error(cm->of);
}

char *replace_first_substring(char *str, char *old_sub, char *new_sub)
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
		return NULL;
	ft_strlcpy(result, str, pos - str + 1);
	result[pos - str] = '\0';
	ft_strlcat(result, new_sub, ft_strlen(result) + new_len + 1);
	ft_strlcat(result, pos + old_len, ft_strlen(result) + ft_strlen(pos + old_len) + 1);
	return result;
}
