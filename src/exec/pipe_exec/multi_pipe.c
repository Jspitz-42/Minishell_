/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jspitz <jspitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:50:45 by jspitz            #+#    #+#             */
/*   Updated: 2025/03/17 12:48:36 by jspitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <parser.h>
#include <pipe_exec.h>
#include <signals.h>

static void	re_init_io_fd(int *fdi, int *fdo)
{
	if (*fdi != -1)
		*fdi = -1;
	if (*fdo != -1)
		*fdo = -1;
}

/**
 * @brief : monitoring inside the monitor
 *
 * @param command : main struct with all input info
 * @param envp : programm environnement
 * @param fds :	fds[0] = before_fd;
 * 				fds[1] = in_fd_redir;
 * 				fds[2] = out_fd_redir;
 */
static void	cmd_to_pipe_2(t_cmd *command, char **envp, t_list *iter, int *fds)
{
	t_subcmd	*scmd;

	set_sig_handler(SIGQUIT, &sigquit_handler_interactive);
	scmd = (t_subcmd *)iter->content;
	if (scmd->outfile != NULL)
		close(command->pipe[1]);
	if (scmd->infile && is_blt((char *)scmd->argv->content))
	{
		if (fds[0] > -1)
			close(fds[0]);
		fds[0] = -1;
		close(command->pipe[0]);
	}
	set_up_stdin(&fds[0], &fds[1]);
	set_up_stdout(iter, command, &fds[2]);
	execute(command, scmd, envp, fds);
	exit(EXIT_SUCCESS);
}

static void	fd_monitor(int fds[3], t_subcmd *scmd)
{
	re_init_io_fd(&fds[1], &fds[2]);
	set_up_redir(&fds[1], &fds[2], scmd);
}

void	cmd_pipex(t_cmd *cmd, char **envp, t_list *iter, t_subcmd *scmd)
{
	int	pid_i;
	int	*fds;

	pid_i = 0;
	fds = (int []){-1, -1, -1};
	while (iter)
	{
		scmd = (t_subcmd *)iter->content;
		fd_monitor(fds, scmd);
		if (iter->next && pipe(cmd->pipe) < 0)
			ft_exec_exit("pipe", 2);
		if (cmd->cmdc == 1 && scmd->argc && is_blt((char *)scmd->argv->content))
			exec_builtins_out_pipe(scmd, fds[2]);
		else if (scmd->argc)
		{
			cmd->pids[pid_i] = fork();
			if (cmd->pids[pid_i] == -1)
				ft_exec_exit("fork", 3);
			if (cmd->pids[pid_i++] == 0)
				cmd_to_pipe_2(cmd, envp, iter, fds);
			set_sig_handler(SIGINT, SIG_IGN);
		}
		cls_scmd_fd(&iter, cmd, scmd, fds);
	}
	wait_all_pid(cmd->pids, pid_i);
}
