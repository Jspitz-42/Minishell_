/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   check_builtins.c                                     ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/02/22 11:36:18 by jspitz               │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/03 07:36:13 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include <pipe_exec.h>

static bool	cd_check_1(const char *path)
{
	struct stat	path_stat;

	if (access(path, F_OK) != 0)
	{
		perror("cd");
		return (false);
	}
	if (stat(path, &path_stat) == 0 && !S_ISDIR(path_stat.st_mode))
	{
		ft_dprintf(2, "cd: %s is Not a directory\n", path);
		return (false);
	}
	if (access(path, R_OK | X_OK) != 0)
	{
		perror("cd");
		return (false);
	}
	return (true);
}

bool	check_cd(t_subcmd *node)
{
	const char	*path;

	if (node->argc < 2)
	{
		ft_dprintf(2, "cd: Missing operand\n");
		return (false);
	}
	if (node->argc > 2)
	{
		ft_dprintf(2, "cd: too many arg\n");
		return (false);
	}
	path = (const char *)node->argv->next->content;
	if (cd_check_1(path) == false)
		return (false);
	return (true);
}

bool	check_env(char **envp)
{
	if (!envp)
		return (false);
	return (true);
}

bool	check_export(t_subcmd *node)
{
	char	*equal_sign;
	char	*var;

	if (node->argc == 1)
	{
		ft_dprintf(2, "export : missing arg\n");
		return (false);
	}
	var = (char *)node->argv->next->content;
	equal_sign = ft_strchr(var, '=');
	if (!equal_sign)
	{
		ft_dprintf(2, "export : invalid format. use VAR=VALUE\n");
		return (false);
	}
	return (true);
}

bool	check_pwd(t_subcmd *node)
{
	if (node->argc > 1)
	{
		ft_dprintf(2, "no option allowed\n");
		return (false);
	}
	return (true);
}
