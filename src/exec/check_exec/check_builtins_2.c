/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   check_builtins_2.c                                   ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/02/22 11:47:21 by jspitz               │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/03 08:23:02 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include <pipe_exec.h>

bool	check_unset(t_subcmd *node)
{
	const char	*val;

	if (node->argc > 2)
	{
		ft_dprintf(2, "unset : too many arg\n");
		return (false);
	}
	val = (const char *)node->argv->content;
	if (!val || ft_strlen(val) == 0)
	{
		ft_dprintf(2, "unset: invalid var name\n");
		return (false);
	}
	return (true);
}

static int	check_builtins_helper(char *cmd, char **envp, t_subcmd *node)
{
	if (ft_strcmp(cmd, "unset") == 0 && !check_unset(node))
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0 && !check_pwd(node))
		return (1);
	else if (ft_strcmp(cmd, "env") == 0 && !check_env(envp))
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0 && !check_cd(node))
		return (1);
	else if (ft_strcmp(cmd, "export") == 0 && !check_export(node))
		return (1);
	return (0);
}

bool	check_all_builtins(t_cmd *cmd, char **envp)
{
	char		*builtins;
	t_subcmd	*node;
	t_list		*iter;

	iter = cmd->subs;
	while (iter)
	{
		node = (t_subcmd *)iter->content;
		if (node->argc == 0)
			return (true);
		else
			builtins = (char *)node->argv->content;
		if (is_blt(builtins))
		{
			if (check_builtins_helper(builtins, envp, node) == 1)
				return (false);
		}
		iter = iter->next;
	}
	return (true);
}
