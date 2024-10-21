#include "./minishell.h"

static	void ft_exit_tool(char *str)
{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ms()->exit = 2;
}
/*
	@return
	0: the str is not a number;
	1: the str is a number;
*/
static int	ft_isnum(char	*str)
{
	int i;

	i = 0;
	while(str[i])
		if(!ft_isdigit(str[i++]))
			return(0);
	return (1);
}

/*
	@return
	0: the str is a valid value;
	1: the str is not a valid value;
*/
int	isvalid(char *str)
{
	int	sign;

	sign = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = 1;
		str++;
	}
	if (!ft_isnum(str))
		return (1);
	if (ft_strlen(str) > 19)
		return (1);
	if (sign)
		return (ft_strcmp(str, "9223372036854775808") > 0);
	else
		return (ft_strcmp(str, "9223372036854775807") > 0);
}
/*
	There are 4 different cases;
	1. input:		exit
	   output:		exit
	   exit_code:	0
	   exit bash?	yes

	2. input: 		exit 1 (here should be a number)
	   output:		exit
	   exit_code:	1 % 256 (num % 256)
	   exit bash?	yes

	3. input:		exit 1 2/ exit 2 a ....(can add more agrument)
	   output:		exit
	   				bash: exit: too many arguments
	   exit_code	1
	   exit bash?	no

	4. input:		exit a....(can add more agrument)
	   output:		exit
					bash: exit: a: numeric argument required
	   exit_code:	2
	   exit bash?	yes
*/
void	ft_exit(char **cmd)
{
	int	i;

	i = ms()->cmds->ct_w;
	if (isvalid(cmd[1])) // as long the cmd[1] is not a valid number, it goes into this branch.
		ft_exit_tool(cmd[1]);
	else if (i > 2 && !isvalid(cmd[1]))
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		ms()->exit = 1;
		return ;
	}
	else if (i <= 2)
	{
		ft_putstr_fd("exit\n", 1);
		ms()->exit = 0;
		if (i == 2 && ft_atoi(cmd[1]) >= 0)
			ms()->exit = ft_atoi(cmd[1]) % 256;
		else
			ms()->exit = ft_atoi(cmd[1]) + 256;
	}
	restart (true);
}

// void	ft_exit(char **cmd)
// {
// 	int	i;

// 	i = 0;
// 	while(cmd[i])
// 		i++;
// 	if (i > 2 && ft_isnum(cmd[1]))
// 	{
// 		ft_putstr_fd("exit\n", 1);
// 		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
// //		ms()->exit = 2;// should be 1, not 2
// 		ms()->exit = 1;
// 	}
// 	else if (i > 2 && !ft_isnum(cmd[1]))
// 		ft_exit_tool(cmd[1]);
// 	if (i == 2 && isvalid(cmd[1]))
// 		ft_exit_tool(cmd[1]);
// 	else if (i == 2)
// 	{
// 		ft_putstr_fd("exit\n", 1);
// 		ms()->exit = ft_atoi(cmd[1]) % 256;
// 	}
// 	restart(1);
// }

