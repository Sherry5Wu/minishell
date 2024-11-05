/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 09:53:18 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/05 15:03:18 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_env(char	*envname, char	*src)
{
	int		i;
	int		j;
	char	*dest;
	char	*replacement;

	replacement = NULL;
	i = 1;
	j = 0;
	while (isprint(envname[i]) && envname[i] != ' ' && envname[i] != '\0')
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

static	char	*checkdollar(char	*doc_in)
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

void	getdoc(char *av, int hfd)
{
	char	*doc_in;

	ms()->heredoc_count = 0;
	while (1)
	{
		doc_in = get_next_line(0);
		if (!doc_in)
		{
			ms()->heredoc_count = -1;
			free(doc_in);
			break ;
		}
		doc_in = checkdollar(doc_in);
		if (ft_strncmp(doc_in, av, ft_strlen(av)) == 0)
		{
			free(doc_in);
			break ;
		}
		ft_putstr_fd(doc_in, hfd);
		free(doc_in);
	}
}

pid_t	type_hdoc(t_cmd *cm)
{

	pid_t	pid;

	signal_ignore();
	pid = fork();
	if (pid == -1)
		ex_error("Fork", FORK, EXIT_FAILURE);
	if (pid == 0)
	{
		ms()->limiter_count = 0;
	signal_ignore();
	signal_heredoc();
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
	signal_default();
	exit(0);
	}

	return (pid);

}

pid_t	type_outpipe(t_cmd *cm, int	*prev_fd)
{
	pid_t	pipeid;

	if (pipe(ms()->fd) == -1)
		ex_error("Pipe", PIPE, EXIT_FAILURE);
	pipeid = exe_pipe(cm);
	close(ms()->fd[1]);
	if (*prev_fd != -1)
		close(*prev_fd);
	*prev_fd = ms()->fd[0];
	return (pipeid);
}
