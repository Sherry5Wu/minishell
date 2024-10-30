/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 09:04:56 by yzheng            #+#    #+#             */
/*   Updated: 2024/10/29 17:21:56 by yzheng           ###   ########.fr       */
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
	if(ms()->in_fd == -1)
		exit(ms()->exit);
	if (cm->intype == TK_HDOC)
		cm->ifnum++;
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
