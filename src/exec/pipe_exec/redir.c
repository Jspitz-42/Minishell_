/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jspitz <jspitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:48:13 by jspitz            #+#    #+#             */
/*   Updated: 2025/03/17 13:45:04 by jspitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipe_exec.h>
#include <parser.h>
#include <builtins.h>

void	cls_scmd_fd(t_list **iter, t_cmd *cmd, t_subcmd *scmd, int *b_fd)
{
	if (b_fd[0] > 0)
		close(b_fd[0]);
	if (b_fd[1] > 0)
		close(b_fd[1]);
	if (b_fd[2] > 0)
		close(b_fd[2]);
	if ((*iter)->next)
	{
		b_fd[0] = cmd->pipe[0];
		close(cmd->pipe[1]);
	}
	if (scmd->in_fd > 0)
		close(scmd->in_fd);
	if (scmd->out_fd > 1)
		close(scmd->out_fd);
	*iter = (*iter)->next;
}

static void	set_up_redir_nhd(int *in_fd, t_subcmd *scmd)
{
	*in_fd = open(scmd->infile->from, O_RDONLY);
	if (*in_fd == -1)
	{
		perror("open");
		return ;
	}
}

void	set_up_redir(int *in_fd, int *out_fd, t_subcmd *scmd)
{
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (scmd->infile && scmd->infile->mode == MODE_HEREDOC)
		*in_fd = scmd->pipe[0];
	if (scmd->infile && scmd->infile->mode != MODE_HEREDOC)
		set_up_redir_nhd(in_fd, scmd);
	if (scmd->outfile)
	{
		if (scmd->outfile->append_mode)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		*out_fd = open(scmd->outfile->to, flags, 0644);
		if (*out_fd == -1)
		{
			perror("open");
			return ;
		}
	}
}

void	set_up_stdin(int *before_fd, int *in_fd_redir)
{
	if (*in_fd_redir != -1)
	{
		if (dup2(*in_fd_redir, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(4);
		}
		close(*in_fd_redir);
		if (*before_fd > -1)
			close(*before_fd);
	}
	else if (*before_fd != -1)
	{
		if (dup2(*before_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(4);
		}
		close(*before_fd);
	}
}

void	set_up_stdout(t_list *iter, t_cmd *command, int *out_fd_redir)
{
	if (*out_fd_redir != -1)
	{
		if (dup2(*out_fd_redir, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(4);
		}
		close(*out_fd_redir);
	}
	else if (iter->next && *out_fd_redir < 0)
	{
		if (dup2(command->pipe[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(5);
		}
		close(command->pipe[1]);
	}
	if (iter->next)
		close(command->pipe[0]);
}
