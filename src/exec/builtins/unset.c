/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ottomata <ottomata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:22:39 by jspitz            #+#    #+#             */
/*   Updated: 2025/03/08 20:34:41 by ottomata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <pipe_exec.h>
#include <environ.h>

void	ft_unset(const char *var)
{
	if (!var)
	{
		ft_dprintf(2, "unset: invalid variable name\n");
		return ;
	}
	remove_from_env_by_key(var);
}
