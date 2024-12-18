/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:09:56 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/02 15:10:44 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(void)
{
	int	i;

	i = 0;
	while (ms()->env[i])
	{
		if (ms()->env[i] == NULL || !ms()->env[i])
			break ;
		ft_printf("%s\n", ms()->env[i++]);
	}
	ms()->exit = 0;
	return (1);
}
