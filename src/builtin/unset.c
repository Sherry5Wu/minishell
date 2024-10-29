#include "minishell.h"

void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list	*cur;
	t_env	*env;

	if (begin_list == NULL || *begin_list == NULL)
		return ;
	cur = *begin_list;
	env = (t_env *)(cur->content);
	if (cmp(env->name, data_ref, ft_strlen(data_ref)) == 0)
	{
		*begin_list = cur->next;
		free(cur);
		ft_list_remove_if(begin_list, data_ref, cmp);
	}
	else
	{
		cur = *begin_list;
		ft_list_remove_if(&cur->next, data_ref, cmp);
	}
}

static int	find_env(char	*name)
{
	int	i;

	i = 0;
	while (ms()->env[i] && !ft_strnstr(ms()->env[i], name, ft_strlen(name)))
		i++;
	if (!ms()->env[i])
		return (0);
	return (i);
}

static void	remove_env(int index)
{
	int	i;

	i = index;
	while (ms()->env[i])
	{
		ms()->env[i] = ms()->env[i + 1];
		i++;
	}
}

int	ft_unset(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[++i])
	{
		ft_list_remove_if(&ms()->env_list, cmd[i], ft_strncmp);
		remove_env(find_env(cmd[i]));
	}
	ms()->exit = 0;
	return (1);
}
