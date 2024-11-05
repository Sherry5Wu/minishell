1.11

1. fixed one memory leak (cat <out)
	pre_handle.c ----> restruct_token()

2. fixed "cat < " didn't show error message issue
	lexer.c ----> lexer()

3. fixed memory leak: export leak #25-#30
	export.c  --> ft_export();
4.	changes
  restart.c
	--> ft_lstclear((&ms()->env_list), (void (*)(void *))free_env); untested.
	--> free.c --> free_env()
	--> minishell.h --> void	free_env(t_env *env)

debugging: ls >./outfiles/outfile01
weird things: if don't add exe part, there is no leak; otherwise, there is leak
			   but the leak shows in the pre_handle part.

5. changed the logic of unset.c ---> ft_list_remove_if()
	the way to get the real value is (t_env *)cur->content)->name



Memory leaks as below:

85/146

