/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   cd.c                                                 ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/01/15 11:05:16 by jspitz               │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/03 07:36:13 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <pipe_exec.h>

static int	cd_check_1(const char *path)
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

void	ft_cd(t_subcmd *node)
{
	const char	*path;

	if (!node->argv->next)
	{
		ft_dprintf(2, "cd: Missing operand\n");
		return ;
	}
	if (node->argv->next->next)
	{
		ft_dprintf(2, "cd: too many arg\n");
		return ;
	}
	path = (const char *)node->argv->next->content;
	if (cd_check_1(path) == false)
		return ;
	if (chdir(path) == -1)
	{
		perror("cd");
	}
}
