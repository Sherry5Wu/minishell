/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:09:11 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/11 13:53:10 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	ft_echo(char **cmd)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (cmd[1] && !ft_strcmp(cmd[1], "-n"))
	{
		n = 1;
		i++;
	}
	while (cmd[++i])
	{
		printf("%s", cmd[i]);
		if (cmd[i] && cmd[i + 1])
			printf(" ");
	}
	if (!cmd[1] || !n)
		printf("\n");
	ms()->exit = 0;
	return (1);
}