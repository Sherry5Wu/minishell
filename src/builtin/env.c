#include "minishell.h"

/*
	if can't find path in env it will stuck at readline so no need to
	check that
*/
int	ft_env(void)
{
	int	i;

	i = 0;
	while (ms()->env[i])
		ft_printf("%s\n", ms()->env[i++]);
	ms()->exit = 0;
	return (1);
}
