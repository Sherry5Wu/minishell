
#include "minishell.h"

int	ft_env(void)
{
	int	i;

	/*if can't find path in env it will stuck at readline so no need to check that*/
	i = 0;
	while(ms()->env[i])
	{
		if (ms()->env[i] == NULL || !ms()->env[i])
			break ;
		ft_printf("%s\n",ms()->env[i++]);
	}
	ms()->exit = 0;
	return(1);
}
