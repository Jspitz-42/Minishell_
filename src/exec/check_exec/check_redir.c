/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   check_redir.c                                        ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/02/22 09:58:36 by jspitz               │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/03 08:23:10 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include <pipe_exec.h>

static bool	check_outfile(t_subcmd *scmd)
{
	int	flags;
	int	fd;

	fd = -1;
	flags = O_WRONLY | O_CREAT;
	if (scmd->outfile)
	{
		if (scmd->outfile->append_mode)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		fd = open(scmd->outfile->to, flags, 0644);
		if (fd == -1)
		{
			perror("open");
			return (false);
		}
		else
			close(fd);
	}
	return (true);
}

bool	check_all_files(t_cmd *cmd)
{
	int			count;
	t_list		*iter;
	t_subcmd	*current;

	iter = cmd->subs;
	count = 0;
	while (iter)
	{
		current = (t_subcmd *)iter->content;
		if (current->infile && current->infile->mode != MODE_HEREDOC)
		{
			if (access(current->infile->from, F_OK | R_OK) < 0)
			{
				ft_dprintf(2, "no '%s' file\n", current->infile->from);
				count++;
			}
		}
		if (current->outfile && !check_outfile(current))
			count++;
		iter = iter->next;
	}
	if (count == 0)
		return (true);
	return (false);
}
