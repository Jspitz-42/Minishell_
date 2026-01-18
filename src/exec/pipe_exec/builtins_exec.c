/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jspitz <jspitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:18:11 by jspitz            #+#    #+#             */
/*   Updated: 2025/03/17 10:35:58 by jspitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipe_exec.h>
#include <parser.h>
#include <builtins.h>

char	**build_argv(char **argv, t_subcmd *node)
{
	int		i;
	t_list	*argv_iter;

	i = 0;
	argv_iter = node->argv;
	while (argv_iter)
	{
		argv[i++] = (char *)argv_iter->content;
		argv[i] = 0;
		argv_iter = argv_iter->next;
	}
	return (argv);
}

int	is_blt(char *argv)
{
	if (ft_strcmp(argv, "cd") == 0)
		return (true);
	else if (ft_strcmp(argv, "echo") == 0)
		return (true);
	else if (ft_strcmp(argv, "env") == 0)
		return (true);
	else if (ft_strcmp(argv, "exit") == 0)
		return (true);
	else if (ft_strcmp(argv, "export") == 0)
		return (true);
	else if (ft_strcmp(argv, "pwd") == 0)
		return (true);
	else if (ft_strcmp(argv, "unset") == 0)
		return (true);
	return (false);
}

static bool	redir_out_builtins(t_cmd *cmd, t_subcmd *node, int *fdo)
{
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (!node->outfile)
		return (true);
	if (node->outfile && node->outfile->append_mode)
		flags |= O_APPEND;
	if (node->outfile)
	{
		close(cmd->pipe[1]);
		*fdo = open((const char *)node->outfile->to, flags, 0644);
	}	
	close(cmd->pipe[0]);
	if (*fdo < 0)
	{
		perror("open");
		core_set_last_exit(127);
		return (false);
	}
	return (true);
}

void	exec_builtins(t_cmd *cmd, t_subcmd *node, char *argv[256], int *fds)
{
	if (!redir_out_builtins(cmd, node, &fds[2]))
		return ;
	if (ft_strcmp(argv[0], "cd") == 0)
		ft_cd(node);
	else if (ft_strcmp(argv[0], "echo") == 0)
		ft_echo(node->argc, argv, fds[2]);
	else if (ft_strcmp(argv[0], "env") == 0)
		ft_env(core_envp(), fds[2]);
	else if (ft_strcmp(argv[0], "exit") == 0)
		ft_exit(node->argc, argv);
	else if (ft_strcmp(argv[0], "export") == 0)
		ft_export(argv[1]);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		ft_pwd(fds[2]);
	else if (ft_strcmp(argv[0], "unset") == 0)
		ft_unset(argv[1]);
	if (fds[2] > 0)
		close(fds[2]);
	if (fds[1] > 0)
		close(fds[1]);
}

void	exec_builtins_out_pipe(t_subcmd *node, int fdo)
{
	char	*argv[256];

	build_argv(argv, node);
	if (ft_strcmp(argv[0], "cd") == 0)
		ft_cd(node);
	else if (ft_strcmp(argv[0], "echo") == 0)
		ft_echo(node->argc, argv, fdo);
	else if (ft_strcmp(argv[0], "env") == 0)
		ft_env(core_envp(), fdo);
	else if (ft_strcmp(argv[0], "exit") == 0)
		ft_exit(node->argc, argv);
	else if (ft_strcmp(argv[0], "export") == 0)
		ft_export(argv[1]);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		ft_pwd(fdo);
	else if (ft_strcmp(argv[0], "unset") == 0)
		ft_unset(argv[1]);
	if (fdo > 0)
		close(fdo);
}
