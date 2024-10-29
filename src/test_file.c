#include "minishell.h"

/*
	1: print tokens
	2: print env;
	3: print local variable
*/
void	print_list(t_list *list, int flag)// for test !!!!!!!!!!!!!!!!!!!!!!!!
{
	t_token	*token;
	t_env	*env;
	int		i;

	i = 0;
	if (!list)
	{
		printf ("token list is empty\n\n");
		return ;
	}

	while (list)
	{
		if (flag == 1)
		{
			token = list->content;
			printf("token[%d]: str=%s   type=%u  arg=%s  index=%d  merger=%d\n", i, token->str, token->tk_type, token->arg, token->idx, token->merge);
		}
		else if (flag == 2)
		{
			env = list->content;
			printf("env[%d]: name=%s   value=%s\n", i, env->name, env->value);
		}
		else if (flag == 3)
		{
			env = list->content;
			printf("local_var[%d]: name=%s   value=%s\n", i, env->name, env->value);
		}
		i++;
		list = list->next;
	}
	printf ("\n\n");
}

void	print_cmd(void)// for test !!!!!!!!!!!!!!!!!!!!!!!!
{//printf("get into print_cmd function\n");// for test !!!!!!!!!!!!!!!!!!!!!!!
	t_cmd	*cmd;
	int  i_cmd = 0;
	int	j;
	t_env	*env;

	if (!ms()->cmds)
	{
		printf ("cmd list is empty\n\n");
		return ;
	}

	cmd = ms()->cmds;
	while (cmd)
	{
		j = 0;
		printf("cmd[%d]\n", i_cmd++);
		printf("ofnum=%d  ifnum=%d  herenum=%d  word=%d\n", cmd->ofnum, cmd->ifnum, cmd->herenum, cmd->word);
		if (cmd->word != 0)
		{
			printf("\ncmd strs are below:\n");
			while(j < cmd->word)
			{
				printf("	cmd_str[%d]=%s\n", j, cmd->cmd[j]);
				j++;
			}
		}
		j = 0;
		if (cmd->ifnum != 0)
		{
			printf("\ninfile strs are below:\n");
			while(j < cmd->ifnum)
			{
				printf("	infile[%d]=%s\n", j, cmd->infile[j]);
				j++;
			}
		}
		j = 0;
		if (cmd->ofnum != 0)
		{
			printf("\noutfile strs are below:\n");
			while(j < cmd->ofnum)
			{
				printf("	outfile[%d]=%s\n", j, cmd->outfile[j]);
				j++;
			}
		}
		j = 0;
		if (cmd->herenum)
		{
			printf("\nlimiter strs are below:\n");
			while(j < cmd->herenum)
			{
				printf("	limiter[%d]=%s\n", j, cmd->limiter[j]);
				j++;
			}
		}
		printf("\nlast_infile=%s\nlast_outfie=%s", cmd->inf, cmd->of);
		printf("\nintype=%d\nouttype=%d\n\n", cmd->intype, cmd->outype);
		if (cmd->iolist)
		{
			j = 0;
			while (cmd->iolist)
			{
				env = cmd->iolist->content;
				printf("env[%d]: name=%s   value=%s\n", j, env->name, env->value);
				j++;
				cmd->iolist = cmd->iolist->next;
			}
		}
		cmd = cmd->next;
	}

	printf ("\n\n");
}


void	print_env(char *name, int size)
{
	t_list	*head;
	int		i;
	t_env	*env;

	head = ms()->env_list;
	i = 0;
	while (ms()->env[i] && !ft_strnstr(ms()->env[i], name, size))
		i++;
	while (head)
	{
		env = (t_env *)(head->content);
		if (!ft_strcmp(env->name, name))
			break ;
		head = head->next;
	}
	printf("ms()->env[%d]=%s\n", i, ms()->env[i]);// for testing!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	printf("env->name=%s\nenv->value=%s\n\n", env->name, env->value);// for testing!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
}
