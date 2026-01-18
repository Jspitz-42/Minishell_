/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   push.c                                               ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/03/08 16:08:45 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/17 15:49:53 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include "va_internals.h"
#include <vecarr.h>

int	va_push(t_vecarr *v, void *item)
{
	void	*tmp;

	if (!v->data)
	{
		v->data = gc_calloc(VECARR_INIT, sizeof(void **));
		if (!v->data)
			return (-1);
		v->allocd = VECARR_INIT;
	}
	else if (v->len >= v->allocd)
	{
		tmp = gc_realloc(v->data, v->allocd * sizeof(void **), v->allocd
				* v->step * sizeof(void **));
		if (!tmp)
			return (-1);
		v->data = tmp;
		v->allocd *= v->step;
	}
	v->data[v->len] = item;
	v->len++;
	return (0);
}
