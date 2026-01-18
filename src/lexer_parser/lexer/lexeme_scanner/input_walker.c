/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   input_walker.c                                       ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/03/13 16:13:40 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/17 10:28:59 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	redirections(char c)
{
	if (c == '|')
		return (add_token(PIPE));
	else if (c == '>')
	{
		if (scanner()->match('>'))
			return (add_token(GREAT_GREAT));
		else
			return (add_token(GREAT));
	}
	else if (c == '<')
	{
		if (scanner()->match('<'))
			return (add_token(LESS_LESS));
		else
			return (add_token(LESS));
	}
	return (0);
}

static int	symbols(char c)
{
	if (c == '#')
	{
		while (scanner()->peek() && scanner()->peek() != '\n')
			scanner()->advance();
		return (1);
	}
	else if (c == '&')
	{
		if (scanner()->match('&'))
			return (add_token(AND));
		else
			return (add_token(AMPERSAND));
	}
	else if (c == ';')
		return (add_token(SEMICOLON));
	return (0);
}

void	scan_token(void)
{
	char	c;

	c = scanner()->advance();
	if (symbols(c) || redirections(c))
		return ;
	if (c == '"' || c == '\'')
		string(c);
	else if (c == '$')
		identifier();
	else if (lit_check(c))
		literal();
	else if (isspace(c))
	{
		while (scanner()->peek() && isspace(scanner()->peek()))
			scanner()->advance();
		add_token(WHITESPACE);
	}
}
