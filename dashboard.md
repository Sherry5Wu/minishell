fixed bugs or changes:
1. changed builtin(), to handle input like these "expor" or "exporta"
2. norm checking for builtin folder, signal folder and pre_handle folder
3. export.c: changed ft_valid_character(), ft_export()
4. cd:

 unfixed known bugs:
 1. export n= 2 --> didn't add n=2 to the env_list and env strs;
	export n=2 m=3 --> m=3 didn't not add to env_list and env strs;


 2. cat <<HEREDOC --> segmentation fault

 3. # keep track of OLDPWD
			cd obj
			echo $PWD $OLDPWD
			cd: after excute "cd src/", it didn't really go to the src folder

		note:
			after fixing, I was backtrace the PWD and OLDPWD value, before in in_exe_pipe2()
			the values were correct. But in in_exe_pipe2() the values are wrong.

		result:
			minishell:/home/jingwu/projects/minishell$ cd src/
			After update the pwd:
			ms()->env[16]=PWD=/home/jingwu/projects/minishell/src
			env->name=PWD
			env->value=/home/jingwu/projects/minishell/src

			ms()->env[48]=OLDPWD=/home/jingwu/projects/minishell
			env->name=OLDPWD
			env->value=/home/jingwu/projects/minishell

			In Real_execute:
			ms()->env[16]=PWD=/home/jingwu/projects/minishell/src
			env->name=PWD
			env->value=/home/jingwu/projects/minishell/src

			ms()->env[48]=OLDPWD=/home/jingwu/projects/minishell
			env->name=OLDPWD
			env->value=/home/jingwu/projects/minishell

			In exe_pipe2:
			ms()->env[16]=PWD=/home/jingwu/projects/minishell
			env->name=PWD
			env->value=/home/jingwu/projects/minishell


4. #invalid command, followed by empty variable, should clear the exit code
	doesntexist
	$EMPTY
	echo $?

5. unset: doesn't unset the variable

