/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   destroy.c                                            ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/03/08 17:19:49 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/12 09:19:42 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include <vecarr.h>

void	va_clear(t_vecarr **v)
{
	long	i;

	if (!v)
		return ;
	i = 0;
	while (i < (*v)->len)
		gc_free((*v)->data[i++]);
	gc_free((*v)->data);
	gc_free(*v);
	v = 0;
}

void	va_destroy(t_vecarr **v)
{
	if (!v)
		return ;
	gc_free((*v)->data);
	gc_free(*v);
	v = 0;
}
