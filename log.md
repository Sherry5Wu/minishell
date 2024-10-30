30.10  changes

1. add free function for env_list
	free.c
	restart.c
	minishell.h
2.  add new error message
	restart.c ---> add an new function print_sig_info();
3. change the logic how to allocate memory for new cmd and how to free cmd list
	parsing.c
	process_re.c
	free.c

