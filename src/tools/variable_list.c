/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 07:56:08 by jingwu            #+#    #+#             */
/*   Updated: 2024/10/28 13:34:12 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	The syntax of defining  enviroment varible: name=value
	Rule:
	1. there is no space between "name", "=" and "value", like
	   name =123, name= 123 are all wrong;
	2. the variable name only start with either letter or '_', and only
	   contains letter, '_' and number.
	   like 2name=123, *name=123, na$me=123 are all wrong;

	f_equal: when loop the str, if encounter a "=" then f_equal=true;
	f_alp_uds: when loop the str, if encounter a alphabeta or "_", then
				f_alp_uds=true;

	@return
	true: is a valid variable defination
	false: is an INVAILD variable defination
*/
bool	is_defining_var(char *str)
{
	int		i;
	bool	f_equal;
	bool	f_alp_uds;

	i = -1;
	f_equal = false;
	f_alp_uds = false;
	while (str[++i])
	{
		if (str[i] == '=')
			f_equal = true;
		else if (str[i] == '_' || ft_isalpha(str[i]))
			f_alp_uds = true;
		else if (!ft_isalpha(str[i]) && str[i] != '_'
			&& !f_equal && !f_alp_uds)// the name start with non-alpha, non-'_', is illegal.
				return (false);
		else if (!ft_isalnum(str[i]) && str[i] != '_'
			&& !f_equal)// there is illegal character in the name.
			return (false);
	}
	if (f_equal == false)
		return (false);
	return (true);
}

t_env	*new_variable(char *name, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = name;
	new->value = value;
	return (new);
}

/*
	@Why "return(ft_strdup(""))"?
	return(ft_strdup("")) and return (NULL) are both return a NULL, but using
	former one, it will generate a memoery for it. In other function, we need
	free the memory we allocate for env_value, so if we just return a NULL with
	out allocating memory for it, it will generate an error.
*/
char	*get_variable_value(char *env_name)
{
	t_env	*env;
	t_list	*tmp;

	if (env_name[0] == '$')
		env_name++;
	tmp = ms() ->env_list;

	while (tmp && env_name)
	{
		env = (t_env *)(tmp->content);
		if (!ft_strcmp(env->name, env_name))
			return (ft_strdup(env->value));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

/*
	@function
	The funtion will loop the env list to find if any env.name matching with passed name.

	@return
	return the env if found matched one;
	return NULL, if did NOT find matched one;
*/
static t_env	*find_variable(t_list *list, char *name)
{
	t_env	*env;

	if (!list)
		return (NULL);
	while (list)
	{
		env = list->content;
		if (!ft_strcmp(env->name, name))
			return (env);
		list = list->next;
	}
	return (NULL);
}

void	add_node_to_list(t_list **list, char *str)
{
	char	*name;
	char	*value;
	int		i;
	t_env	*env;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			break;
	}
	name = ft_substr(str, 0, i);
	value = ft_strdup(str + i + 1);
	env = find_variable(*list, name);
	if (env)
	{
		free(name);
		free(env->value);
		env->value = value;
	}
	else
		ft_lstadd_back(list, ft_lstnew(new_variable(name, value)));
}
