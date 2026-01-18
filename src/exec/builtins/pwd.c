/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jspitz <jspitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:39:50 by jspitz            #+#    #+#             */
/*   Updated: 2025/03/06 07:39:08 by jspitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>

void	ft_pwd(int fd_out)
{
	char	*current_directory;
	char	buff[4097];

	if (fd_out == -1)
		fd_out = 1;
	current_directory = getcwd(buff, sizeof(buff));
	if (!current_directory)
	{
		perror("Error getting current directory");
		return ;
	}
	ft_dprintf(fd_out, "%s\n", current_directory);
}
