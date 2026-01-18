/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ottomata <ottomata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 06:40:18 by tblochet          #+#    #+#             */
/*   Updated: 2025/03/08 23:21:38 by ottomata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	*command(void)
{
	t_cmd	*cmd;

	cmd = gc_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->error = true;
	cmd->subs = 0;
	return (cmd);
}

void	insert_subcmd(t_cmd *cmd, t_subcmd *subcmd)
{
	t_gclist	*node;

	if (!cmd || !subcmd)
		return ;
	node = ftgc_lstnew(subcmd);
	if (!node)
		return ;
	ftgc_lstadd_back(&cmd->subs, node);
	cmd->cmdc++;
}
