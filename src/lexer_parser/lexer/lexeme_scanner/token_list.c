/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   token_list.c                                         ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/03/17 10:29:25 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/17 16:29:38 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_token_list	*tt_new(t_token *token)
{
	t_token_list	*node;

	node = gc_calloc(1, sizeof(t_token_list));
	if (!node)
		return (0);
	node->token = token;
	node->next = 0;
	node->previous = 0;
	return (node);
}

void	clear_tokens_list(t_token_list **token_list)
{
	t_token_list	*iter;
	t_token_list	*next;
	t_token_list	*lst;

	if (!token_list)
		return ;
	lst = *token_list;
	if (!lst)
		return ;
	iter = lst;
	while (iter)
	{
		next = iter->next;
		if (iter && iter->token)
		{
			gc_free(iter->token->lexeme);
			gc_free(iter->token);
		}
		gc_free(iter);
		iter = next;
	}
	*token_list = 0;
}

void	append_token(t_token_list **token_list, t_token *token)
{
	t_token_list	*tmp;
	t_token_list	*new;

	new = tt_new(token);
	if (!new)
		return ;
	if (!(*token_list))
	{
		*token_list = new;
		return ;
	}
	tmp = *token_list;
	while (tmp)
	{
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	new->previous = tmp;
	tmp->next = new;
}
