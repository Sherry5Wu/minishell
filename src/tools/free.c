
#include "minishell.h"

void	ft_free_str(void *pointer)
{
	if (pointer)
		free(pointer);
	pointer = NULL;
}

void	pp_free(char **fly)
{
	int	j;

	if (!fly || !*fly)
		return ;
	j = 0;
	while (fly[j])
			free(fly[j++]);
	free(fly);
	fly = NULL;
}

/*
	For free the content of iolist.
*/
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
		pp_free(ms()->cmds->cmd);
		pp_free(ms()->cmds->infile);
		pp_free(ms()->cmds->limiter);
		pp_free(ms()->cmds->outfile);
		free(ms()->cmds->of);
		free(ms()->cmds->inf);
		ft_lstclear((&(ms()->cmds->iolist)), (void (*)(void *))free_env2);
		free(ms()->cmds);
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
		free(temp);
		temp = next_node;
	}
	ms()->local_var = NULL;
}
void	free_env(t_env *env)
{
	ft_free_str(env->name);
	ft_free_str(env->value);
	ft_free_str(env);
	env = NULL;
}
