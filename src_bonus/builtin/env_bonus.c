/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:09:56 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/11 13:53:12 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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
