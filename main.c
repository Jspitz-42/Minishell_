/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   main.c                                               ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/01/20 18:08:04 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/17 13:34:25 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <defines.h>
#include <environ.h>
#include <input.h>
#include <lexer.h>
#include <parser.h>
#include <readline/readline.h>
#include <sys/wait.h>

int		g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	if (set_sig_handler(SIGINT, &sigint_handler_main))
		exit(EXIT_FAILURE);
	core()->env = setup(envp);
	readline_wrapper(envp);
	return (0);
}
