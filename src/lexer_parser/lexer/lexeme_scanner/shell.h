/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   shell.h                                              ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/03/13 16:11:51 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/17 13:48:28 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include <libft.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_token_type	t_token_type;
typedef enum e_expr_type	t_expr_type;
typedef struct s_scanner	t_scanner;
typedef struct s_token		t_token;
typedef struct s_token_list	t_token_list;

enum						e_token_type
{
	PIPE = 0,
	EQUAL,
	STAR,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
	IDENTIFIER,
	DSTRING,
	SSTRING,
	AMPERSAND,
	AND,
	OR,
	LEFT_PAREN,
	RIGHT_PAREN,
	SEMICOLON,
	LITERAL,
	WHITESPACE,
	EOL,
	ERROR,
};

struct						s_token
{
	t_token_type			type;
	char					*lexeme;
	int						line;
	int						pos;
};

struct						s_token_list
{
	t_token					*token;
	t_token_list			*next;
	t_token_list			*previous;
};

struct						s_scanner
{
	int						start;
	int						current;
	int						line;
	int						encountered_error;
	char					*source;
	t_token_list			*tokens;
	int						_init;
	int						_src_len;
	int						(*is_at_end)(void);
	char					(*advance)(void);
	int						(*match)(char);
	char					(*peek)(void);
};

t_scanner					*scanner(void);
t_scanner					*rescanner(void);
t_token_list				*scan_tokens(char *source);

int							is_at_end(void);
char						advance(void);
char						peek(void);
int							match(char c);

int							add_token(int token_type);
void						add_token_full(t_token_type token_type,
								char *lexeme);
int							lit_check(char c);
void						scan_token(void);

void						string(char str_type);
void						identifier(void);
void						identifier_expander(void);
void						literal(void);
void						literal_accumulator(void);

int							any_valid_next(t_token_list *lst);
int							any_valid_previous(t_token_list *lst);
int							is_redir(t_token_type toktype);
int							syntax_check(t_token_list *lst);

void						lex_warn(char *text, int line, int pos);
void						lex_error(char *text, int line, int pos);
void						lex_fatal(char *origin);
void						clear_tokens_list(t_token_list **token_list);
void						append_token(t_token_list **token_list,
								t_token *token);
t_token_list				*tt_new(t_token *token);
void						cleanup_tokens(void);
#endif
