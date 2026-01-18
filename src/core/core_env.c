/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   core_env.c                                           ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/02/15 13:10:53 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/12 09:01:17 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <environ.h>
#include <libft.h>

char	*core_getenv(char *name)
{
	size_t	len;
	char	*entry;

	if (!name)
		return (0);
	len = ft_strlen(name);
	entry = get_env_entry_from_key(name);
	if (!entry)
		return (0);
	return (entry + len + 1);
}

char	*core_envp_as_string(void)
{
	t_vecarr	*env;

	env = core()->env;
	if (!env)
		return (0);
	return (env->join(env, "\n"));
}

char	**core_envp(void)
{
	t_vecarr	*env;
	char		**_envp;
	long		i;

	env = core()->env;
	if (!env)
		return (0);
	_envp = gc_calloc(env->len + 1, sizeof(char **));
	if (!_envp)
		return (0);
	i = 0;
	while (i < env->len)
	{
		_envp[i] = env->data[i];
		i++;
	}
	return (_envp);
}
