
#include "minishell.h"

t_ms	*ms(void)
{
	static t_ms ms;
	return(&ms);
}

char	*prompt()
{
	char	*str;
	char	*str2;

	str = ft_strjoin(GREEN"minishell:"RESET_C , ms()->cwd);// delete the color settings
	if (!str)
		return(NULL);
	str2 = ft_strjoin(str,"$ ");
	if (!str2)
	{
		free(str);
		return(NULL);
	}
	free(str);
	return(str2);
}

char	*findpath(char **env)
{

	int	i;

	i = 0;
	while (env[i] && !ft_strnstr(env[i], "PATH", 4))
		i++;
	return (env[i]);

}
void	buildshell()
{
	while (1)
	{
		ms()->path = findpath(ms()->env);
		ms()->prompt = prompt();
		ms()->input = readline(ms()->prompt);
		ms()->lines++;
		if(!ms()->input)
		{
			ft_printf("exit\n");
			restart(1);
		}
		add_history(ms()->input);
		if(ft_strlen(ms()->input)>0)
			pre_handle();
			// if (pre_handle())
			// 	exe(ms()->cmds);
		restart(0);
	}
}


t_list *get_env_list(char **envs)
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

static void initenv(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	ms()->env = malloc((i + 1) * sizeof(char *));
	if (ms()->env == NULL)
		exit(1);
	i = 0;
	while(env[i])
	{
		ms()->env[i] = ft_strdup(env[i]);
		if (ms()->env[i] == NULL)
		{
			while(i)
				free(ms()->env[i--]);
			exit(1);
		}
		i++;
	}
	ms()->env[i] = NULL;
}

static void init_ms(char **env)
{

	ft_bzero(ms(),sizeof(t_ms));
	ms()->exit = 0;
	ms()->in_fd = STDIN_FILENO;
	ms()->out_fd = STDOUT_FILENO;
	ms()->hfd = -1;
	ms()->cwd = getcwd(NULL, 2048);
	ms()->env_list = get_env_list(env);
	initenv(env);
	ms()->lines= 0;
	ms()->fd[0] = -1;
	ms()->fd[1] = -1;
	if(!(ms()->cwd))
	{
		perror("getcwd() error");
		exit(1);
	}
}

int main(int  ac, char **av, char **env)
{
	if (ac != 1)
	{
		ft_putstr_fd("Too many arguments\n",2);
		exit(127);
	}
	(void)av;
	init_ms(env);
	signal_default();
	buildshell();
	return (ms()->exit);
}

