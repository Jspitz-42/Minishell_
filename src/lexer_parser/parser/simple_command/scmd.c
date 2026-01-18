/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   scmd.c                                               ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/01/08 06:28:23 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/03 08:30:59 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

t_subcmd	*scmd_create(void)
{
	t_subcmd	*cmd;

	cmd = gc_calloc(1, sizeof(t_subcmd));
	if (!cmd)
		return (0);
	cmd->argc = 0;
	cmd->argv = 0;
	cmd->outfile = 0;
	cmd->infile = 0;
	return (cmd);
}

void	scmd_destroy(t_subcmd *scmd)
{
	if (!scmd)
		return ;
	ft_lstclear(&scmd->argv, free);
	if (scmd->outfile)
		gc_free(scmd->outfile->to);
	gc_free(scmd->outfile);
	if (scmd->infile)
	{
		gc_free(scmd->infile->from);
		gc_free(scmd->infile->heredoc_lim);
	}
	gc_free(scmd->infile);
	gc_free(scmd);
}
