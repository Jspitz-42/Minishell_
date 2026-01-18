/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   literal_accumulator.c                                ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/03/17 10:17:41 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/17 10:48:13 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	acc_check(t_token_type type)
{
	return (type == SSTRING || type == DSTRING || type == LITERAL);
}

void	literal_accumulator(void)
{
	t_token_list	*it;
	t_token_list	*nx;
	char			*tmp;

	it = scanner()->tokens;
	while (it)
	{
		nx = it->next;
		while (nx && acc_check(it->token->type))
		{
			if (acc_check(nx->token->type))
			{
				tmp = ftgc_strjoin(it->token->lexeme, nx->token->lexeme);
				gc_free(nx->token->lexeme);
				nx->token->lexeme = 0;
				gc_free(it->token->lexeme);
				it->token->lexeme = tmp;
			}
			else
				break ;
			nx = nx->next;
		}
		it = nx;
	}
}
