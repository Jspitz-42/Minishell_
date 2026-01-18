/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jspitz <jspitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:52:11 by jspitz            #+#    #+#             */
/*   Updated: 2025/03/12 13:43:02 by jspitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipe_exec.h>

char	*relative_absolute_command(char const *cmd)
{
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	ft_dprintf(2, "error cmd '%s' not executable\n", cmd);
	return (NULL);
}

void	execute_relative(char **argv, char **envp)
{
	struct stat	path_stat;

	if (stat(argv[0], &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		ft_dprintf(2, "potishell: '%s' is a directory\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if (access(argv[0], X_OK) < 0)
	{
		perror("potishell");
		exit(EXIT_FAILURE);
	}
	else if (execve(argv[0], argv, envp) < 0)
	{
		error_execve(argv[0]);
	}
}

void	execute_end(char *path, char **argv, char **envp)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		ft_dprintf(2, "potishell: '%s' is a directory\n", argv[0]);
		gc_clear();
		exit(EXIT_FAILURE);
	}
	else if (execve(path, argv, envp) < 0)
		return (error_execve(path));
}
