/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 20:27:59 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/12 13:47:27 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_str(void *pointer)
{
	if (pointer)
		free(pointer);
	pointer = NULL;
}

void	pp_ft_free_str(char **fly)
{
	int	j;

	if (!fly || !*fly)
		return ;
	j = 0;
	while (fly[j])
		ft_free_str(fly[j++]);
	ft_free_str(fly);
	fly = NULL;
}

static void	free_env2(t_env *env)
{
	ft_free_str(env->name);
	ft_free_str(env);
	env = NULL;
}

void	free_cmd_list(void)
{
	t_cmd	*next_cmd;

	if (!ms()->cmds)
		return ;
	while (ms()->cmds)
	{
		next_cmd = ms()->cmds->next;
		pp_ft_free_str(ms()->cmds->cmd);
		pp_ft_free_str(ms()->cmds->infile);
		pp_ft_free_str(ms()->cmds->limiter);
		pp_ft_free_str(ms()->cmds->outfile);
		if (ms()->cmds->ofnum)
			ft_free_str(ms()->cmds->of);
		if (ms()->cmds->ifnum)
			ft_free_str(ms()->cmds->inf);
		ft_lstclear((&(ms()->cmds->iolist)), (void (*)(void *))free_env2);
		ft_free_str(ms()->cmds);
		ms()->cmds = next_cmd;
	}
	ms()->cmds = NULL;
}

void	free_local_var_list(void)
{
	t_list	*temp;
	t_list	*next_node;
	t_env	*var;

	if (ms()->local_var == NULL)
		return ;
	temp = ms()->local_var;
	while (temp)
	{
		var = (t_env *)temp->content;
		next_node = temp->next;
		ft_free_str(var->name);
		ft_free_str(var->value);
		ft_free_str(temp);
		temp = next_node;
	}
	ms()->local_var = NULL;
}
