/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   cleanup_tokens.c                                     ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/03/17 13:45:09 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/17 16:21:50 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	cleanup_tokens(void)
{
	t_token_list	*iter;
	t_token_list	*next;
	t_token_list	*tmp;

	iter = scanner()->tokens;
	while (iter)
	{
		next = iter->next;
		if (iter->token->type == WHITESPACE)
		{
			tmp = iter->previous;
			if (iter->previous)
				iter->previous->next = next;
			if (iter->next)
				iter->next->previous = tmp;
			gc_free(iter->token);
			gc_free(iter);
		}
		iter = next;
	}
}
