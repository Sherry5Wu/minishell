
#include "minishell.h"

static void	handle_in_re(t_cmd **cmd, t_list *tk_node)
{
	t_env	*redir;
	t_token	*token;
	char	*token_type;

	token = (t_token *)tk_node->content;
	(*cmd)->intype = TK_IN_RE;
	(*cmd)->infile[(*cmd)->ct_in++]
		= ft_strdup(token->arg);
	if ((*cmd)->ct_in == (*cmd)->ifnum)
		(*cmd)->inf = ft_strdup(token->arg);
	token_type = ft_strdup("2");
	redir = new_variable(token_type, (token->arg));
	ft_lstadd_back(&((*cmd)->iolist), ft_lstnew(redir));
}

static void	handle_hdoc(t_cmd **cmd, t_list *tk_node)
{
	(*cmd)->intype = TK_HDOC;
	(*cmd)->limiter[(*cmd)->ct_del++]
		= ft_strdup(((t_token *)((tk_node)->content))->arg);
}

static void	handle_out_re(t_cmd **cmd, t_list *tk_node)
{
	t_env	*redir;
	t_token	*token;
	char	*token_type;

	token = (t_token *)tk_node->content;
	(*cmd)->outype = token->tk_type;
	(*cmd)->outfile[(*cmd)->ct_out++]
		= ft_strdup(token->arg);
	if ((*cmd)->ct_out == (*cmd)->ofnum)
		(*cmd)->of = ft_strdup(token->arg);
	if (token->tk_type == TK_OUT_RE)
		token_type = ft_strdup("3");
	else
		token_type = ft_strdup("5");
	redir = new_variable(token_type, (token->arg));
	ft_lstadd_back(&((*cmd)->iolist), ft_lstnew(redir));
}

void	process_re(t_cmd **cmd, t_list *tk_node)
{
	t_token	*token;

	token = (t_token *)(tk_node->content);
	if (token->tk_type == TK_IN_RE)
		handle_in_re(cmd, tk_node);
	else if (token->tk_type == TK_HDOC)
		handle_hdoc(cmd, tk_node);
	else if (token->tk_type == TK_OUT_RE || token->tk_type == TK_APPEND)
		handle_out_re(cmd, tk_node);
}

