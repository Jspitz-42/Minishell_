/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ottomata <ottomata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:38:24 by jspitz            #+#    #+#             */
/*   Updated: 2025/03/08 20:56:19 by ottomata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <pipe_exec.h>

void	ft_env(char **envp, int fd_out)
{
	int		i;

	if (fd_out == -1)
		fd_out = 1;
	if (!envp || !*envp)
		return ;
	i = 0;
	while (i < 256 && envp[i])
	{
		if (ft_strlen(envp[i]))
			ft_putendl_fd(envp[i], fd_out);
		i++;
	}
}
