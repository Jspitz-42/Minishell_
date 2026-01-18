/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   setup.c                                              ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/03/08 19:48:29 by ottomata             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/11 13:21:24 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include <environ.h>

t_vecarr	*setup(char **envp)
{
	int			i;
	t_vecarr	*dynenv;

	i = 0;
	if (!envp)
		return (0);
	dynenv = va_new();
	if (!dynenv)
		return (0);
	while (envp[i])
		dynenv->push(dynenv, ftgc_strdup(envp[i++]));
	return (dynenv);
}
