/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ottomata <ottomata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:08:04 by jspitz            #+#    #+#             */
/*   Updated: 2025/03/08 21:11:23 by ottomata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <environ.h>
#include <pipe_exec.h>

static void	export_error(const char *s)
{
	ft_dprintf(2, "%s\n", (char *)s);
}

void	ft_export(char *var)
{
	char	*key;

	if (!var)
		return (export_error("export: missing arg"));
	if (!ft_strchr(var, '='))
		return (export_error("export: invalid format. Use VAR=VALUE"));
	key = ft_substr(var, 0, ft_strcspn(var, "="));
	remove_from_env_by_key(key);
	free(key);
	insert_env_kv_pair(var);
}
