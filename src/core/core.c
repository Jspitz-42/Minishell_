/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ottomata <ottomata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:59:22 by tblochet          #+#    #+#             */
/*   Updated: 2025/03/08 20:42:11 by ottomata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>

int	core_set_last_exit(int status)
{
	core()->last_exit = status;
	return (status);
}

t_core	*core(void)
{
	static t_core	core = {0};

	if (!core.init_ok)
	{
		core.init_ok = 1;
		core.env = 0;
	}
	return (&core);
}
