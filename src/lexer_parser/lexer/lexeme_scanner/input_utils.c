/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   input_utils.c                                        ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/03/13 16:21:00 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/17 15:49:17 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	add_token_full(t_token_type token_type, char *lexeme)
{
	t_scanner	*scnr;
	t_token		*token;

	scnr = scanner();
	token = gc_calloc(1, sizeof(t_token));
	if (!token)
		return ;
	token->type = token_type;
	token->line = scnr->line;
	token->pos = scnr->start;
	token->lexeme = lexeme;
	append_token(&scnr->tokens, token);
}

int	add_token(int token_type)
{
	add_token_full(token_type, 0);
	return (1);
}

int	lit_check(char c)
{
	return (!ft_isspace(c) && c != '>' && c != '<' && c != '|' && c != '*'
		&& c != '\'' && c != '"' && c != '$');
}
