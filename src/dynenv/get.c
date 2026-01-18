/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   get.c                                                ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/03/08 20:19:11 by ottomata             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/12 09:01:14 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <environ.h>

char	*get_env_entry_from_key(char const *key)
{
	long		i;
	size_t		keylen;
	t_vecarr	*env;

	if (!key)
		return (0);
	env = core()->env;
	keylen = ft_strlen(key);
	i = 0;
	while (i < env->len)
	{
		if (ft_strncmp((char const *)env->data[i], key, keylen) == 0)
			if (((char *)env->data[i])[keylen] == '=')
				return ((char *)env->data[i]);
		i++;
	}
	return (0);
}

long	get_env_index_from_key(char const *key)
{
	long		i;
	size_t		keylen;
	t_vecarr	*env;

	if (!key)
		return (0);
	env = core()->env;
	keylen = ft_strlen(key);
	i = 0;
	while (i < env->len)
	{
		if (ft_strncmp((char const *)env->data[i], key, keylen) == 0)
			if (((char *)env->data[i])[keylen] == '=')
				return (i);
		i++;
	}
	return (-1);
}
