/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ottomata <ottomata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 20:02:11 by ottomata          #+#    #+#             */
/*   Updated: 2025/03/08 21:11:42 by ottomata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <environ.h>

int	replace_env_value(char const *value)
{
	char		*key;
	t_vecarr	*env;
	int			ret;

	if (!value)
		return (-1);
	env = core()->env;
	if (!env)
		return (1);
	key = ft_substr(value, 0, ft_strcspn(value, "="));
	ret = remove_from_env_by_key(key);
	if (ret)
		ft_dprintf(2, "minishell: Error code %d for key %s\n", ret, key);
	free(key);
	env->push(env, (void *)value);
	return (0);
}
