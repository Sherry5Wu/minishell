
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
// void	token_delete(t_token *token)
// {
// 	if (!token)
// 		return ;
// 	ft_free_str(token->arg);
// 	ft_free_str(token->str);
// 	token->tk_type = -1;
// 	token->merge = 0;
// 	token->idx = -1;
// 	ft_free_str(token);
// }
void	free_token_list(void)
{
	t_list	*temp;
	t_list	*next_node;
	t_token	*token;

	if (ms()->tokens == NULL)
		return ;
	temp = ms()->tokens;
	while (temp)
	{
		token = temp->content;
		next_node = temp->next;
		ft_free_str(token->arg);
		ft_free_str(token->str);
		if (token)
			free(token);
		free(temp);
		temp = next_node;
	}
	ms()->tokens = NULL;
}

// static void	free_iolist(t_list *list)
// {
// 	t_list	*temp;
// 	t_list	*next_node;
// 	t_env	*var;

// 	if (list == NULL)
// 		return ;
// 	temp = list;
// 	while (temp)
// 	{

// 		next_node = temp->next;
// 		var = (t_env *)temp->content;
// 		ft_free_str(var->name);
// 		ft_free_str(var->value);
// 		if (var)
// 			free(var);
// 		free(temp);
// 		temp = next_node;
// 	}
// 	list = NULL;
// }
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
		ft_free_str(ms()->cmds->of);
		ft_free_str(ms()->cmds->inf);
//		free_iolist(ms()->cmds->iolist);
		ft_lstclear(&(ms()->env_list), (void(*)(void *))free_env);
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
	free(env);
}
