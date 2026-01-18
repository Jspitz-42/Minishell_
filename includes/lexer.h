/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   lexer.h                                              ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/01/08 03:03:29 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/13 16:30:46 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <libft.h>
# include "../src/lexer_parser/lexer/lexeme_scanner/shell.h"

/**
 * @brief Tokenize a NULL terminated string representing a shell command.
 * @param raw Input string
 * @return Linked list with each tokens of the raw input.
 * NULL in case of error.
 */
t_list							*tokenize(char *raw);

#endif
