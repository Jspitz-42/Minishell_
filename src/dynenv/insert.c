/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ottomata <ottomata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 20:15:21 by ottomata          #+#    #+#             */
/*   Updated: 2025/03/08 20:44:47 by ottomata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environ.h>
#include <core.h>

int	insert_env_kv_pair(char const *value)
{
	t_vecarr	*env;

	env = core()->env;
	return (env->push(env, (void *)value));
}
