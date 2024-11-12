/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 20:21:20 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/12 13:47:18 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	buildshell(void)
{
	while (1)
	{
		ms()->hstatus = 0;
		ms()->path = findpath(ms()->env);
		ms()->prompt = prompt();
		ms()->input = readline(ms()->prompt);
		ms()->lines++;
		if (!ms()->input)
		{
			ft_printf("exit\n");
			restart(1);
		}
		add_history(ms()->input);
		if (ft_strlen(ms()->input) > 0)
			if (pre_handle())
				exe(ms()->cmds);
		if (ms()->exit != 130)
			restart(0);
	}
}

static t_list	*get_env_list(char **envs)
{
	t_list	*env_lt;
	int		i;

	i = 0;
	env_lt = NULL;
	while (envs[i])
	{
		add_node_to_list(&env_lt, envs[i]);
		i++;
	}
	return (env_lt);
}

static void	initenv(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	ms()->env = malloc((i + 1) * sizeof(char *));
	if (ms()->env == NULL)
		exit(1);
	i = 0;
	while (env[i])
	{
		ms()->env[i] = ft_strdup(env[i]);
		if (ms()->env[i] == NULL)
		{
			while (i)
				ft_free_str(ms()->env[i--]);
			exit(1);
		}
		i++;
	}
	ms()->env[i] = NULL;
}

static void	init_ms(char **env)
{
	ft_bzero(ms(), sizeof(t_ms));
	ms()->exit = 0;
	ms()->in_fd = STDIN_FILENO;
	ms()->out_fd = STDOUT_FILENO;
	ms()->hfd = -1;
	(ms()->cwd) = getcwd(NULL, 2048);
	ms()->env_list = get_env_list(env);
	initenv(env);
	ms()->lines = 0;
	ms()->fd[0] = -1;
	ms()->fd[1] = -1;
	if (!(ms()->cwd))
	{
		perror("getcwd() error");
		exit(1);
	}
}

int	main(int ac, char **av, char **env)
{
	if (ac != 1)
	{
		ft_putstr_fd("Too many arguments\n", 2);
		exit(127);
	}
	(void)av;
	init_ms(env);
	signal_default();
	buildshell();
	return (ms()->exit);
}
