/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:02:58 by yzheng            #+#    #+#             */
/*   Updated: 2024/10/28 19:15:24 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_error(char *message)
{
	if (!access(message, F_OK))
		exit(126);
	else
		exit(1);

}

void	ex_error(char *message, t_err_type type, int err_status)
{
	ft_putstr_fd("minishell: ", 2);
	if(message)
		ft_putstr_fd(message, 2);
	if (type == DIRECTORY)
		ft_putstr_fd(" : Is a directory", 2);
	else if (type == COMMAND)
		ft_putstr_fd(" : command not found", 2);
	else if  (type == NFILE)
		ft_putstr_fd(" : No such file or directory", 2);
	else if  (type == PREMISSON)
		ft_putstr_fd(" : Permission denied", 2);
	else if  (type == FORK)
		ft_putstr_fd(" : fork failed", 2);
	else if  (type == PIPE)
		ft_putstr_fd(" : pipe failed", 2);
	else if  (type == ERR)
		ft_putstr_fd(strerror(errno), 2);
	else if  (type == TOOMUCH)
		ft_putstr_fd(" : too many arguments", 2);
	else if  (type == HOME)
		ft_putstr_fd(" : HOME not set", 2);
	ft_putchar_fd('\n', 2);
	exit(err_status);
}

bool	print_error(char *err_type, int err_fd)
{
	ft_putstr_fd(err_type, STDERR_FILENO);
	write(2, "\n", 1);
	ms() ->exit = err_fd;
	return (false);
}

bool	stx_error(t_token *node)
{
	if (!node)
		print_error(NL_STX_ERR, 1);
	else if (node->tk_type == TK_PIPE)
		print_error(PIPE_STX_ERR, 1);
	else if (node->tk_type == TK_IN_RE)
		print_error(IN_RE_STX_ERR, 1);
	else if (node->tk_type == TK_OUT_RE)
		print_error(OUT_RE_STX_ERR, 1);
	else if (node->tk_type == TK_HDOC)
		print_error(HDOC_STX_ERR, 1);
	else if (node->tk_type == TK_APPEND)
		print_error(APED_STX_ERR, 1);
	return (false);
}
int	export_err(char	*cmd)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	ms()->exit = 1;
	return (0);
}

int	print_sorted_env()
{
	int	i;
	int	j;
	char	**envsort;

	i = 0;
	j = 0;
	envsort = sort_env();
	while (ms()->env[i])
	{
		j = 0;
		printf("declare -x ");
		while(envsort[i][j] != '=')
			printf("%c",envsort[i][j++]);
		j++;
		printf("=\"");
		while(envsort[i][j])
			printf("%c",envsort[i][j++]);
		printf("\"\n");
		i++;
	}
	free(envsort);
	return(1);
}
