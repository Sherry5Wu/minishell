/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 09:53:18 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/08 13:05:13 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_env(char *envname, char *src)
{
	int		i;
	int		j;
	char	*dest;
	char	*replacement;

	replacement = NULL;
	i = 1;
	j = 0;
	while (ft_isprint(envname[i]) && envname[i] != ' ' && envname[i] != '\0')
		i++;
	dest = ft_strndup(envname, i);
	if (dest == NULL)
		return (NULL);
	while (ms()->env[j] && !ft_strnstr(ms()->env[j], dest + 1, i - 1))
		j++;
	if (!ms()->env[j])
		replacement = "";
	else
		replacement = ms()->env[j] + i;
	dest = replace_first_substring(src, dest, replacement);
	return (dest);
}

static char	*checkdollar(char *doc_in)
{
	char	*dc;
	int		i;

	i = 0;
	while (doc_in[i])
	{
		dc = ft_strchr(doc_in + i, '$');
		if (dc && *(dc + 1) && *(dc + 1) != '\n' && *(dc + 1) != ' ')
		{
			doc_in = replace_env(dc, doc_in);
			i = 0;
		}
		i++;
	}
	return (doc_in);
}

static void	getdoc(char *av, int hfd)
{
	char	*doc_in;

	ms()->heredoc_count = 0;
	while (1)
	{
		doc_in = readline(">");
		if (!doc_in)
		{
			ms()->heredoc_count = -1;
			free(doc_in);
			break ;
		}
		doc_in = checkdollar(doc_in);
		if (ft_strncmp(doc_in, av, ft_strlen(av)) == 0
			&& ft_strlen(doc_in) == ft_strlen(av))
		{
			free(doc_in);
			break ;
		}
		ft_putstr_fd(doc_in, hfd);
		ft_putstr_fd("\n", hfd);
		free(doc_in);
	}
}

void	heredoc(t_cmd *cm)
{
	signal_heredoc();
	ms()->limiter_count = 0;
	while (cm->herenum--)
	{
		(ms()->hfd) = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (ms()->hfd == -1)
			open_error("here_doc");
		getdoc(cm->limiter[ms()->limiter_count++], ms()->hfd);
		close(ms()->hfd);
	}
	if (cm->intype == TK_HDOC)
	{
		cm->intype = TK_IN_RE;
		cm->inf = "here_doc";
		set_fd(cm);
	}
}
