/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   input_functions.c                                    ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/03/13 16:19:46 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/17 14:04:42 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	literal(void)
{
	t_scanner		*scnr;
	t_token_type	type;

	scnr = scanner();
	type = LITERAL;
	while (scnr->peek() && lit_check(scnr->peek()))
		scnr->advance();
	add_token_full(type, ftgc_strndup(scnr->source + scnr->start, scnr->current
			- scnr->start));
}

void	identifier(void)
{
	t_scanner	*scnr;

	scnr = scanner();
	if (scnr->match('?'))
		add_token_full(IDENTIFIER, ftgc_strdup("?"));
	else
	{
		while (scnr->peek() && (ft_isalnum(scnr->peek())
				|| scnr->peek() == '_'))
			scnr->advance();
		add_token_full(IDENTIFIER, ftgc_strndup(scnr->source + scnr->start + 1,
				scnr->current - scnr->start - 1));
	}
}

void	string(char str_type)
{
	t_scanner		*scnr;
	t_token_type	type;

	scnr = scanner();
	type = DSTRING;
	if (str_type == '\'')
		type = SSTRING;
	while (scnr->peek() && scnr->peek() != str_type)
		scnr->advance();
	if (scnr->peek() != str_type)
	{
		lex_error("Unterminated string", scnr->line, scnr->start);
		return ;
	}
	add_token_full(type, ftgc_strndup(scnr->source + scnr->start + 1,
			scnr->current - scnr->start - 1));
	scnr->advance();
}
