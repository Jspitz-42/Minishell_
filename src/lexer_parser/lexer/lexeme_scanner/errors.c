/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   errors.c                                             ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/03/13 16:27:02 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/17 13:39:06 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <defines.h>

void	lex_fatal(char *origin)
{
	perror(origin);
	exit(EXIT_FAILURE);
}

void	lex_warn(char *text, int line, int pos)
{
	printf("Warning: [line %d, char %d] %s\n", line, pos + 1, text);
}

void	lex_error(char *text, int line, int pos)
{
	char	*underline;

	scanner()->encountered_error = 1;
	underline = ft_calloc(ft_strlen(scanner()->source) + 1, sizeof(char));
	if (underline)
	{
		ft_memset(underline, '~', ft_strlen(scanner()->source));
		underline[pos] = '^';
		ft_dprintf(2, "  %s\n  " RED "%s\n" DEFAULT, scanner()->source,
			underline);
		free(underline);
	}
	ft_dprintf(2, "Error: [line %d, char %d] %s\n", line, pos + 1, text);
}
