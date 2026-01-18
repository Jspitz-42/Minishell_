/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   scanner.c                                            ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/03/13 16:11:02 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/17 10:16:34 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_scanner	*scanner(void)
{
	static t_scanner	scnr = {0};

	if (!scnr._init)
	{
		scnr.start = 0;
		scnr.current = 0;
		scnr.line = 1;
		scnr._init = 1;
		scnr.is_at_end = &is_at_end;
		scnr.advance = &advance;
		scnr.peek = &peek;
		scnr.match = &match;
		scnr.tokens = 0;
	}
	return (&scnr);
}

t_scanner	*rescanner(void)
{
	t_scanner	*scnr;

	scnr = scanner();
	scnr->line = 1;
	scnr->start = 0;
	scnr->current = 0;
	scnr->tokens = 0;
	scnr->encountered_error = 0;
	return (scnr);
}
