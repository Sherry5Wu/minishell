/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 08:43:11 by jingwu            #+#    #+#             */
/*   Updated: 2024/11/06 10:25:26 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	The name doesn't not contain the '$' at the beginning.
	For example:
		1. $cat, will just return "$cat" as the env_name;
*/
static char	*get_env_name(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '$')
		i++;
	if (str[i] == '?')
		return (ft_strdup("$?"));
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (ft_substr(str, 0, i));
}

/*
	The function will replace name with value, then return the newstr.
*/
static char	*replace(char *str, char *name, char *value)
{
	int		len;
	char	*newstr;
	char	*tmp;
	char	*bef_name;

	if (!str | !name | !value)
		return (ft_strdup(""));
	len = ft_strlen(str) + ft_strlen(value) - ft_strlen(name);
	newstr = ft_calloc((len + 1), sizeof(char));
	if (!newstr)
		return (ft_strdup(""));
	tmp = ft_strnstr(str, name, (ft_strlen(str)));
	bef_name = ft_substr(str, 0, (tmp - str));
	ft_strlcat(newstr, bef_name, (len + 1));
	ft_strlcat(newstr, value, (len + 1));
	ft_strlcat(newstr, (tmp + ft_strlen(name)), len + 1);
	free(bef_name);
	return (newstr);
}

static void	expand(t_token *token)
{
	char	*name;
	char	*value;
	char	*tmp;

	while (ft_strnstr(token->str, "$", ft_strlen(token->str)))
	{
		name = get_env_name(ft_strchr(token->str, '$'));
		if (!name)
			return ;
		if (!ft_strcmp(name, "$?"))
			value = ft_itoa(ms()->exit);
		else
			value = get_variable_value(name);
		tmp = token->str;
		token->str = replace(token->str, name, value);
		free(name);
		free(value);
		free(tmp);
	}
}

/*
	@How to check if the env is needed expaned or not?
	Rule: when env is quoted by double quote, or not quoted, they need to
	expand.
	The conditions need to be considerd:
		1. echo $?
		2. echo $$name
		3. echo "$name' abc"
		4. echo 'abc $name out"put'
	Rule:
	If you can find the variable, then replace the value, otherwise, delete
	the token.For example "$EMPTY echo hi", there is no EMPTY in the variable
	list, then delete it,just pass "echo hi" to the execution part.
*/
void	expander(void)
{
	t_token	*token;
	char	*str;

	tk_list_manager(RESET);
	while (tk_list_manager(CUR_CNT))
	{
		token = tk_list_manager(CUR_CNT);
		if (token->tk_type == TK_DOUBLE_QT || token->tk_type == TK_WORD)
		{
			str = ft_strchr(token->str, '$');
			if (str && *(str + 1) != '\0' && *(str + 1) != ' '
				&& (ft_isalnum(*(str + 1)) || *(str + 1) == '_'
					|| *(str + 1) == '?'))
				expand(token);
		}
		tk_list_manager(NEXT);
	}
}
