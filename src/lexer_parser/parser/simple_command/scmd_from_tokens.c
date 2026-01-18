/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   scmd_from_tokens.c                                   ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/01/16 08:43:12 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/17 16:29:27 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include "../../lexer/lexeme_scanner/shell.h"
#include <parser.h>

static int	local_is_redir(t_token_type toktype)
{
	return (toktype == LESS || toktype == LESS_LESS || toktype == GREAT
		|| toktype == GREAT_GREAT);
}

static int	is_cmd_separator(t_token_type toktype)
{
	return (toktype == PIPE);
}

static void	register_redirection(t_subcmd *scmd, t_token_list **tokens,
		t_token_type t)
{
	t_token_list	*l;

	if (!(*tokens) || !(*tokens)->next)
		return ;
	l = (*tokens)->next;
	if (l->token->type == WHITESPACE)
		l = l->next;
	if (t == GREAT || t == GREAT_GREAT)
	{
		if (scmd->outfile)
			ft_dprintf(2,
				"potishell: warning: multiple outward redirections, "
				"using the last one.\n");
		scmd_set_outfile(scmd, ftgc_strdup(l->token->lexeme), t == GREAT_GREAT);
	}
	else
	{
		if (scmd->infile)
			ft_dprintf(2,
				"potishell: warning: multiple inward redirections, "
				"using the last one.\n");
		scmd_set_infile(scmd, ftgc_strdup(l->token->lexeme), t == LESS_LESS);
	}
	(*tokens) = l;
}

static void	setup_default_fd(t_subcmd *scmd)
{
	if (!scmd->infile)
		scmd->in_fd = STDIN_FILENO;
	if (!scmd->outfile)
		scmd->out_fd = STDOUT_FILENO;
}

t_subcmd	*scmd_create_from_tokens(t_token_list **tokens)
{
	t_token		*curr;
	t_subcmd	*s_cmd;

	if (!tokens || !*tokens)
		return (0);
	s_cmd = scmd_create();
	if (!s_cmd)
		return (0);
	while (tokens && *tokens)
	{
		curr = (*tokens)->token;
		if (local_is_redir(curr->type))
			register_redirection(s_cmd, tokens, curr->type);
		else if (is_cmd_separator(curr->type))
		{
			(*tokens) = (*tokens)->next;
			break ;
		}
		else
			scmd_insert_argument(s_cmd, curr->lexeme);
		(*tokens) = (*tokens)->next;
	}
	setup_default_fd(s_cmd);
	return (s_cmd);
}
