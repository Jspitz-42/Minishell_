/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   syntax_utils.c                                       ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/03/17 10:21:50 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/17 10:30:02 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	is_redir(t_token_type toktype)
{
	return (toktype == LESS || toktype == LESS_LESS || toktype == GREAT
		|| toktype == GREAT_GREAT || toktype == PIPE);
}

int	any_valid_previous(t_token_list *lst)
{
	int	found;

	found = 0;
	while (lst)
	{
		if (!is_redir(lst->token->type) && lst->token->type != WHITESPACE)
		{
			found = 1;
			break ;
		}
		lst = lst->previous;
	}
	return (found);
}

int	any_valid_next(t_token_list *lst)
{
	while (lst)
	{
		if (is_redir(lst->token->type))
			return (0);
		if (lst->token->type != WHITESPACE && lst->token->type != EOL)
			return (1);
		lst = lst->next;
	}
	return (0);
}

int	syntax_check(t_token_list *lst)
{
	if (lst->token->type == PIPE)
	{
		if (!any_valid_next(lst->next) || !any_valid_previous(lst->previous))
		{
			lex_error("invalid syntax", lst->token->line, lst->token->pos);
			return (1);
		}
	}
	else if (is_redir(lst->token->type))
	{
		if (!any_valid_next(lst->next))
		{
			lex_error("invalid syntax", lst->token->line, lst->token->pos);
			return (1);
		}
	}
	return (0);
}
