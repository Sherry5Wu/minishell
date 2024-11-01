1.11

1. fixed one memory leak (cat <out)
	pre_handle.c ----> restruct_token()

2. fixed "cat < " didn't show error message issue
	lexer.c ----> lexer()
