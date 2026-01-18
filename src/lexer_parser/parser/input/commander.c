/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   commander.c                                          ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/01/17 13:53:11 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/17 16:25:55 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include "../../lexer/lexeme_scanner/shell.h"
#include <input.h>
#include <parser.h>

static void	setup_heredocs(t_cmd *cmd)
{
	t_list		*iter;
	t_subcmd	*scmd;

	iter = cmd->subs;
	while (iter)
	{
		scmd = (t_subcmd *)iter->content;
		if (scmd->infile)
		{
			if (scmd->infile->mode)
			{
				if (pipe(scmd->pipe) < 0)
					exit(1);
				heredoc(scmd->pipe[1], scmd->infile->heredoc_lim);
				scmd->in_fd = scmd->pipe[0];
			}
		}
		iter = iter->next;
	}
}

t_cmd	*command_from_user_input(char *input)
{
	t_token_list	*tokens;
	t_token_list	*iter;
	t_subcmd		*scmd;
	t_cmd			*cmd;

	tokens = scan_tokens(input);
	iter = tokens;
	cmd = command();
	while (iter)
	{
		scmd = scmd_create_from_tokens(&iter);
		insert_subcmd(cmd, scmd);
	}
	clear_tokens_list(&tokens);
	setup_heredocs(cmd);
	return (cmd);
}
