/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   utils.c                                              ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/01/25 13:48:13 by jspitz               │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/17 13:21:04 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <pipe_exec.h>
#include <signals.h>

void	wait_all_pid(int *pid, int npid)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	while (i < npid)
	{
		waitpid(pid[i], &status, 0);
		status = WEXITSTATUS(status);
		i++;
	}
	set_sig_handler(SIGINT, sigint_handler_main);
	core_set_last_exit(status);
}

void	ft_exec_exit(char *s, int status)
{
	perror(s);
	exit(status);
}

void	error_execve(char *path)
{
	perror("execve error");
	gc_clear();
	if (path)
		free(path);
	exit(EXIT_FAILURE);
}

static char	*full_path_command(char const *cmd, char **paths)
{
	char	*try_path;
	char	**pointer_path;
	char	*tmp;

	pointer_path = paths;
	if (ft_strchr(cmd, '/'))
		return (relative_absolute_command(cmd));
	while (*pointer_path)
	{
		tmp = ft_strjoin((char const *)*pointer_path, "/");
		try_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!try_path)
			return (NULL);
		if (access(try_path, F_OK) == 0)
			return (try_path);
		free(try_path);
		pointer_path++;
	}
	if (is_blt((char *)cmd) == false)
		ft_dprintf(2, "error cmd '%s' not found\n", cmd);
	return (NULL);
}

void	execute(t_cmd *cmd, t_subcmd *node, char **envp, int *fds)
{
	char	*env_path;
	char	**paths;
	char	*path;
	char	*argv[256];

	build_argv(argv, node);
	if (ft_strchr(argv[0], '/'))
		return (execute_relative(argv, envp));
	env_path = core_getenv("PATH");
	if (!env_path)
		env_path = "";
	paths = ft_split(env_path, ':');
	path = full_path_command(argv[0], paths);
	free_2d((void **)paths);
	if (is_blt(argv[0]) == true)
	{
		free(path);
		exec_builtins(cmd, node, argv, fds);
		gc_clear();
		exit(EXIT_SUCCESS);
	}
	if (!path)
		return ;
	execute_end(path, argv, envp);
}
