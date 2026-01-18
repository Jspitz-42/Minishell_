/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   scmd_inserts.c                                       ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/01/17 03:32:36 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/17 13:01:14 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void	scmd_insert_argument(t_subcmd *cmd, char *arg)
{
	char		*arg_dup;
	t_gclist	*node;

	if (!cmd || !arg)
		return ;
	arg_dup = ftgc_strdup(arg);
	if (!arg_dup)
		return ;
	node = ftgc_lstnew(arg_dup);
	if (!node)
	{
		gc_free(arg_dup);
		return ;
	}
	ftgc_lstadd_back(&cmd->argv, node);
	cmd->argc++;
}

void	scmd_set_outfile(t_subcmd *cmd, char *file, int wmode)
{
	t_wredir	*redir;

	if (!cmd || !file)
		return ;
	redir = gc_calloc(1, sizeof(t_wredir));
	if (!redir)
		return ;
	gc_free(cmd->outfile);
	redir->append_mode = wmode;
	redir->to = ftgc_strdup(file);
	cmd->outfile = redir;
}

void	scmd_set_infile(t_subcmd *cmd, char *file, int is_heredoc)
{
	t_rredir	*redir;

	if (!cmd || !file)
		return ;
	redir = gc_calloc(1, sizeof(t_rredir));
	if (!redir)
		return ;
	gc_free(cmd->infile);
	if (is_heredoc)
		redir->heredoc_lim = file;
	else
		redir->from = ftgc_strdup(file);
	redir->mode = is_heredoc;
	cmd->infile = redir;
}
