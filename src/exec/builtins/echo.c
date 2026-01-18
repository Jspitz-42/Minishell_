/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   echo.c                                               ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/01/15 10:56:21 by jspitz               │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/17 14:20:41 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <parser.h>
#include <pipe_exec.h>

void	ft_echo(int ac, char **av, int fd_out)
{
	int	new_line;
	int	i;

	new_line = 1;
	i = 0;
	if (fd_out == -1)
		fd_out = 1;
	if (av[1] && ft_strncmp(av[1], "-n", 2) == 0)
	{
		new_line = 0;
		i = 1;
	}
	while (av[++i])
	{
		if (i != ac - 1)
		{
			if (ft_dprintf(fd_out, "%s ", av[i]) < 0)
				return (perror("potishell: echo"));
		}
		else if (ft_dprintf(fd_out, "%s", av[i]) < 0)
			return (perror("potishell: echo"));
	}
	if (new_line == 1)
		if (ft_dprintf(fd_out, "\n") < 0)
			return (perror("potishell: echo"));
}
