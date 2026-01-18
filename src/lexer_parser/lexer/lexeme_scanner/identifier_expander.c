/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   identifier_expander.c                                ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/03/17 10:18:34 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/17 14:08:01 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <core.h>

void	identifier_expander(void)
{
	t_token_list	*it;
	char			*tmp;

	it = scanner()->tokens;
	while (it)
	{
		if (it->token->type == IDENTIFIER)
		{
			if (ft_strcmp(it->token->lexeme, "?") == 0)
				tmp = ftgc_itoa(core()->last_exit);
			else
			{
				tmp = core_getenv(it->token->lexeme);
				if (!tmp)
					tmp = ftgc_strdup("");
			}
			gc_free(it->token->lexeme);
			it->token->lexeme = tmp;
			it->token->type = LITERAL;
		}
		it = it->next;
	}
}
