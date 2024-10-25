

#include "minishell.h"

pid_t exe_pipe(t_cmd *cm)
{
	pid_t	pid;

	signal_ignore();
	pid = fork();
 	if (pid == -1)
		ex_error("Fork", FORK, EXIT_FAILURE);
	if (pid == 0)
	{
		signal_child();
		if(ms()->in_fd == -1)
			exit(ms()->exit);
		check_infile(cm);
		dup2(ms()->in_fd,STDIN_FILENO);
		dup2(ms()->fd[1],STDOUT_FILENO);
		close(ms()->fd[0]);
		close(ms()->fd[1]);
		real_execute(cm);
	}

	return(pid);
}
pid_t exe_pipe2(t_cmd *cm)
{
	pid_t	pid;
	int status;
	int	i;
	int	ofd;

	signal_ignore();
	pid = fork();
 	if (pid == -1)
		ex_error("Fork", FORK, EXIT_FAILURE);
	if (pid == 0)
	{
		signal_child();
		i = 0;
		ofd = 0;
		while(i < cm->ofnum - 1)
		{
			ofd =open(cm->outfile[i++], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if(ofd == -1)
			{
				close_inout();
				set_error(cm->outfile[--i]);
				exit(1);
			}
			close(ofd);
		}
		if (cm->intype == TK_HDOC)
			cm->ifnum++;
		check_infile(cm);
		if(ms()->in_fd == -1)
			exit(ms()->exit);
		if(dup2(ms()->out_fd,STDOUT_FILENO) == -1 || dup2(ms()->in_fd,STDIN_FILENO) == -1)
		{
			close_inout();
			exit(1);
		}
		close_inout();
		real_execute(cm);
	}
	waitpid(pid,&status,0);
	ms()->exit = WEXITSTATUS(status);

// printf ("In exe_pipe2:\n");// for testing!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
// print_env("PWD", 3); // for testing!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
// print_env("OLDPWD", 6); // for testing!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1

	return(pid);
}

pid_t exe_pipe3(t_cmd *cm)
{
	pid_t	pid;
	int		i;
	int status;
	int ofd;
	signal_ignore();
	pid = fork();
 	if (pid == -1)
		ex_error("Fork", FORK, EXIT_FAILURE);
	if (pid == 0)
	{
		signal_child();

		i = 0;
			ofd = 0;
		while(i < cm->ofnum - 1)
		{
			ofd =open(cm->outfile[i++], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if(ofd == -1)
			{
				close_inout();
				set_error(cm->outfile[--i]);
				exit(1);
			}
			close(ofd);
		}
		dup2(ms()->fd[0],STDIN_FILENO);
		dup2(ms()->out_fd,STDOUT_FILENO);
		if(dup2(ms()->out_fd,STDOUT_FILENO) == -1)
		{
			close(ms()->fd[1]);
			close(ms()->fd[0]);
			exit(1);
		}
		close(ms()->fd[1]);
		close(ms()->fd[0]);
		real_execute(cm);
	}
	waitpid(pid,&status,0);
	ms()->exit = WEXITSTATUS(status);
	return(pid);

}
