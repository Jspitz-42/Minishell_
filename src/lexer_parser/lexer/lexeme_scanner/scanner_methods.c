/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   scanner_methods.c                                    ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/03/13 16:10:57 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/17 16:22:10 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <core.h>

int	is_at_end(void)
{
	t_scanner	*instance;

	instance = scanner();
	return (instance->current >= instance->_src_len);
}

char	advance(void)
{
	t_scanner	*instance;
	int			pos;

	instance = scanner();
	pos = instance->current++;
	return (instance->source[pos]);
}

char	peek(void)
{
	t_scanner	*instance;

	instance = scanner();
	if (instance->is_at_end())
		return (0);
	return (instance->source[instance->current]);
}

int	match(char c)
{
	t_scanner	*instance;

	instance = scanner();
	if (instance->is_at_end())
		return (0);
	if (instance->source[instance->current] != c)
		return (0);
	instance->current++;
	return (1);
}

t_token_list	*scan_tokens(char *source)
{
	t_scanner		*scnr;
	t_token_list	*iter;

	scnr = rescanner();
	scnr->source = source;
	scnr->_src_len = ft_strlen(source);
	while (!scnr->is_at_end())
	{
		scnr->start = scnr->current;
		scan_token();
	}
	iter = scnr->tokens;
	while (iter && !scnr->encountered_error)
	{
		if (syntax_check(iter))
			break ;
		iter = iter->next;
	}
	if (scnr->encountered_error)
		return (clear_tokens_list(&scnr->tokens), (void *)0);
	identifier_expander();
	literal_accumulator();
	return (scnr->tokens);
}
