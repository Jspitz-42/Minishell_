/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   remove.c                                             ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/03/08 20:30:35 by ottomata             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/12 09:01:05 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <environ.h>

int	__env_delete(t_vecarr *v, long index)
{
	if (index >= v->len)
		return (-1);
	if (index < 0)
		index = v->len + index;
	gc_free(v->data[index]);
	ft_memmove(v->data + index, v->data + index + 1, (v->len - index - 1)
		* sizeof(void **));
	v->len--;
	return (0);
}

int	remove_from_env_by_key(char const *key)
{
	t_vecarr	*env;
	long		index;

	env = core()->env;
	if (!env)
		return (-1);
	if (!key)
		return (1);
	index = get_env_index_from_key(key);
	if (index < 0)
		return (2);
	if (__env_delete(env, index))
		return (3);
	return (0);
}
