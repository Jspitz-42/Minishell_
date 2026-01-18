/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   check_command_access.c                               ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/02/22 08:25:08 by jspitz               │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/17 13:20:17 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <pipe_exec.h>

static char	**set_up_check_one_command(void)
{
	char	*paths;
	char	**multi_paths;

	multi_paths = NULL;
	paths = core_getenv("PATH");
	if (!paths)
		paths = "";
	else
		multi_paths = ft_split(paths, ':');
	return (multi_paths);
}

static bool	check_relative(const char *cmd)
{
	struct stat	path_stat;

	if (stat(cmd, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		ft_dprintf(2, "potishell: '%s' is a directory\n", cmd);
		return (false);
	}
	if (access(cmd, X_OK) < 0)
	{
		perror("potishell");
		return (false);
	}
	return (true);
}

static bool	check_one_command(const char *cmd, char **paths)
{
	char	*try_path;
	char	*tmp;
	char	**pointer_path;

	pointer_path = paths;
	if (ft_strchr(cmd, '/') || ft_strchr(cmd, '.') || ft_strlen(cmd) == 0)
		return (check_relative(cmd));
	while (pointer_path && *pointer_path)
	{
		tmp = ft_strjoin((char *)*pointer_path, "/");
		try_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!try_path)
			return (false);
		if (access(try_path, F_OK | X_OK) == 0)
		{
			free(try_path);
			return (true);
		}
		free(try_path);
		pointer_path++;
	}
	ft_dprintf(2, "error command '%s' not found\n", cmd);
	return (false);
}

bool	check_all_command(t_cmd *cmd)
{
	t_list		*current;
	t_subcmd	*node;
	char		**paths;
	char		*argv[256];
	int			count;

	count = 0;
	current = cmd->subs;
	paths = NULL;
	while (current)
	{
		node = (t_subcmd *)current->content;
		if (node->argc == 0)
			return (true);
		build_argv(argv, node);
		paths = set_up_check_one_command();
		if (!is_blt(argv[0]) && !check_one_command(argv[0], paths))
			count++;
		free_2d((void **)paths);
		current = current->next;
	}
	if (count > 0)
		return (false);
	return (true);
}
