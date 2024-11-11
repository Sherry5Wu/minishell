# minishell

The objective of this project is for creating a simple shell. It could seperate as 5 parts: build shell,

pre_handle(parsing), exection, builtin, signal. Among them, the workload of exection part is  largest,

then it is pre_handle.

## Pre_handle

In this part, it will parse the input (when it isn't empty), saving the input in token list

first, then eventually saving it in cmd list. In this process, I used 9 step to implement it.

Token list struct as below:(content is a t_token * type data)
```c
typedef struct list s_list
{
	void	*content;
    struct s_list   *next;
}   t_list;

typedef struct s_token
{
	char			*str;
	t_token_type	tk_type;
	char			*arg;
	bool			merge;
	int				idx;
}	t_token;
```
### Step 1: check_quote

In check_quote, we will check if the input quoted properly. If yes, the pre_handle will continue;

otherwise, it will print the error message and stop the program.

What is a properly quoted input?

Any input as long any single quote or double quote has their matched quote, then the input is properly

quoted.
```c
Like below inputs are inproperly quote:

a. echo "world hello

b. echo 'build'"your'shell
```
### Step 2: lexer

In lexer, we will saving the input into token linked list.

What is token?

Token refers to a single element or unit of text that the shell interprets as part of a command. The shell

breaks down each line of input into tokens before executing the command. There are different types of

tokens, and these tokens are the fundamental building blocks of shell commands.
```c
For example, "ls", "<", ">>", "|", "a word" "-l", they are all tokens.
```
Tokenization process:

Here we will splits the input into tokens using spaces and newlines.

Example:
```c
input=echo $HOME'world' | cat >outfile

Tokens are: echo, hello, world, |, cat, >, outfile.

Token list is:
token[0]=
    str=echo
    tk_type=TK_WORD
    arg=NULL
    merge=0
    idx=-1

Token[1]=
    str=$HOME
    tk_type=TK_WORD
    arg=NULL
    merge=1
    idx=-1

token[2]=
    str=world
    tk_type=TK_SINGLE_QT
    arg=NULL
    merge=0
    idx=-1

Token[3]=
    str=|
    tk_type=TK_PIPE
    arg=NULL
    merge=0
    idx=-1

token[4]=
    str=cat
    tk_type=TK_WORD
    arg=NULL
    merge=0
    idx=-1

Token[5]=
    str=>
    tk_type=TK_OUT_RE (output redirector)
    arg=NULL
    merge=0
    idx=-1

token[6]=
    str=outfile
    tk_type=TK_WORD
    arg=NULL
    merge=0
    idx=-1
```
### Step 3: check_syntax

In check_syntax, we will check syntax errors.
```c
What condistions count as an error?

	1. the input starts with '|';

	2. the input end with <, >, << or >> or next them is antoher meta_char.

	   For exmample:

	   	input:	echo "Do you like minishell?" <

	   	input:	echo "Yes I like it!" < >

	3. the input end with '|' or 2 pipes together

	   For example:

	   	input:	echo "Another happy day" |

		input:	echo "true" | wc -l | | echo error
```
### Step 4: merge

In merge, we will merge the tokens which merge=1 to its previous tokens. Like the previous token list

above, we will meger token[2] into token[1], and delete token[2]. After merge the token list will be:
```c
token[0]=
    str=echo
    tk_type=TK_WORD
    arg=NULL
    merge=0
    idx=-1

Token[1]=
    str=$HOMEworld
    tk_type=TK_WORD
    arg=NULL
    merge=0
    idx=-1

Token[2]=
    str=|
    tk_type=TK_PIPE
    arg=NULL
    merge=0
    idx=-1

token[3]=
    str=cat
    tk_type=TK_WORD
    arg=NULL
    merge=0
    idx=-1

Token[4]=
    str=>
    tk_type=TK_OUT_RE (output redirector)
    arg=NULL
    merge=0
    idx=-1

token[5]=
    str=outfile
    tk_type=TK_WORD
    arg=NULL
    merge=0
    idx=-1
```
### Step 5: restruct_token

In restruct_token, I will while loop the token list to find redictions. If I found token x is a

redirection, then I will copy the next token's str to token x's arg. Because if the current token is a

redirection, the next token must be a filename or a delimater(for heredoc). After we finish the copy part,

then we will delete the next token.

So ater restruct_token part, the above token list will be:
```c
token[0]=
    str=echo
    tk_type=TK_WORD
    arg=NULL
    merge=0
    idx=-1

Token[1]=
    str=$HOMEworld
    tk_type=TK_WORD
    arg=NULL
    merge=0
    idx=-1

Token[2]=
    str=|
    tk_type=TK_PIPE
    arg=NULL
    merge=0
    idx=-1

token[3]=
    str=cat
    tk_type=TK_WORD
    arg=NULL
    merge=0
    idx=-1

Token[4]=
    str=>
    tk_type=TK_OUT_RE (output redirector)
    arg=outfile
    merge=0
    idx=-1
```
### Step 6: expander

In expander, we will expander all the variables to their true values.

The above token list, we will replace $HOME by "/home/jingwu"will be :
```c
token[0]=
    str=echo
    tk_type=TK_WORD
    arg=NULL
    merge=0
    idx=-1

Token[1]=
    str=/home/jingwuworld
    tk_type=TK_WORD
    arg=NULL
    merge=0
    idx=-1

Token[2]=
    str=|
    tk_type=TK_PIPE
    arg=NULL
    merge=0
    idx=-1

token[3]=
    str=cat
    tk_type=TK_WORD
    arg=NULL
    merge=0
    idx=-1

Token[4]=
    str=>
    tk_type=TK_OUT_RE (output redirector)
    arg=outfile
    merge=0
    idx=-1
```
### Step 7: are_all_def_loc_var

In this part, we will check if the input just contains define local variables, such as :

name=jingwu | schoo="hive helsinki". If yes, then the program will restart from here, not going to

execution part.

### Step 8: assign_token_index

In this part, we will assign index to each token(start from 0), before they are all default as -1. Because

in the next step I need the index to create the cmd list. That is why I need this step here.

So the above token list will be:
```c
token[0]=
    str=echo
    tk_type=TK_WORD
    arg=NULL
    merge=0
    idx=0

Token[1]=
    str=/home/jingwuworld
    tk_type=TK_WORD
    arg=NULL
    merge=0
    idx=1

Token[2]=
    str=|
    tk_type=TK_PIPE
    arg=NULL
    merge=0
    idx=2

token[3]=
    str=cat
    tk_type=TK_WORD
    arg=NULL
    merge=0
    idx=3

Token[4]=
    str=>
    tk_type=TK_OUT_RE (output redirector)
    arg=outfile
    merge=0
    idx=4
```
### Step 9: parsing

In parsing, we will use token list to create cmd list. The tokens will be seperate by '|' or newline.

The cmd struct is as below:
```c
typedef struct s_cmd
{
	char			**cmd;
	char			**infile;
	char			**limiter;
	char			**outfile;
	char			*of;
	char			*inf;
	t_token_type	intype;
	t_token_type	outype;
	int				ofnum;
	int				ifnum;
	int				herenum;
	int				word;
	int				ct_in;
	int				ct_out;
	int				ct_del;
	int				ct_w;
	struct s_cmd	*next;
}	t_cmd;
```
the cmd node will be allocate memory and set default value as:
```c
t_cmd *cmds = ft_calloc(1, sizeof(t_cmd));
```
So the above token list will create a cmd list which contains 2 node:
```c
node cmd[0]=
        cmd[0]=echo
        cmd[1]=/home/jingwuworld
        infile=NULL
        limiter=NULL
        outfile=NULL
        of=NULL
        inf=NULL
        intype=TK_NONE
        outype=TK_PIPE
        ofnum=0
        ifnum=0
        herenum=0
        word=2
        ct_in=0
        ct_out=0
        ct_del=0
        ct_w=2

node cmd[1]=
        cmd[0]=cat
        infile=NULL
        limiter=NULL
        outfile[0]=outfile
        of=outfile
        inf=NULL
        intype=TK_PIPE
        outype=TK_OUT_RE
        ofnum=1
        ifnum=0
        herenum=0
        word=1
        ct_in=0
        ct_out=1
        ct_del=0
        ct_w=1
```
More examples:
```c
input=<in1 <in2 ls | <<end <<end1 grep "txt" > out1 >>out2 | echo a

node cmd[0]=
        cmd[0]=ls
        infile[1]=in1
        infile[2]=in2
        limiter=NULL
        outfile=NULL
        of=NULL
        inf=in2
        intype=TK_IN_RE
        outype=TK_PIPE
        ofnum=0
        ifnum=2
        herenum=0
        word=1
        ct_in=2
        ct_out=0
        ct_del=0
        ct_w=1

node cmd[1]=
        cmd[0]=grep
        cmd[1]=txt
        infile=NULL
        limiter[0]=end
        limiter[1]=end1
        outfile[0]=out1
        outfile[1]=out2
        of=out2
        inf=NULL
        intype=TK_PIPE
        outype=TK_APPEND
        ofnum=2
        ifnum=0
        herenum=2
        word=2
        ct_in=0
        ct_out=2
        ct_del=2
        ct_w=2

node cmd[2]=
        cmd[0]=echo
        cmd[1]=a
        infile=NULL
        limiter=NULL
        outfile=NULL
        of=NULL
        inf=NULL
        intype=TK_PIPE
        outype=TK_NONE
        ofnum=0
        ifnum=0
        herenum=0
        word=2
        ct_in=0
        ct_out=0
        ct_del=0
        ct_w=2
```
## Execution

## knowledge sharing

### signal

WIFSIGNALED(status): Nonzero if STATUS indicates termination by a signal.

WTERMSIG(status): Get the signal number if the system is terminated by a

				  siganl.

WIFEXITED(status): Nonzero if STATUS indicates normal termination.

WEXITSTATUS(status): Get the exit status number if it is a normal

					 termination.


### Process exit status

1. Exit Status Range:

	- In Unix-like systems, the exit status of a process is    typically an 8-bit value, which means it can range from 0 to 255.
	- By using the range 0-127 for normal exit statuses and 128-255 for signal-induced terminations, the system can distinguish between normal exits and those caused by signals.

2. Normal Exit Status:

	- When a program terminates normally (for example, it completes its execution successfully), it returns an exit status of 0 (or any other value from 1 to 127) to indicate success or different types of errors.

	- These values represent the successful completion of the program and the return codes defined by the programmer.

3. Signal-Induced Termination:

	- When a process is terminated by a signal (such as SIGINT for interrupt, SIGTERM for termination, or SIGKILL for force termination), the exit status is calculated as 128 + signal number.

	- For example, if a process is terminated by SIGINT, which has a signal number of 2, the exit status would be 128 + 2 = 130.

	- The number 128 is a base value that serves to shift the range of exit statuses for signal-induced terminations.


# Debug

1. -fsanitize
```c
fsanitize is a compiler flag used in GCC and Clang that enables runtime error detection through "sanitizers." Sanitizers help identify various types of bugs, such as memory errors, undefined behavior, and data races, making it easier to debug and improve the stability of your code. Here are some common options:

Address Sanitizer (-fsanitize=address): Detects memory errors, such as buffer overflows, use-after-free, and memory leaks.

Undefined Behavior Sanitizer (-fsanitize=undefined): Catches undefined behavior, such as integer overflows, invalid shifts, and null pointer dereferencing.

Thread Sanitizer (-fsanitize=thread): Identifies data races in multi-threaded programs.
Memory Sanitizer (-fsanitize=memory): Detects uninitialized reads in memory, helping to prevent errors from uninitialized values.
```
2. valgrind --trace-children=yes --track-fds=yes   --? checking if all children thread
    and fd are all closed.
