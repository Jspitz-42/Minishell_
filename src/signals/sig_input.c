/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   sig_input.c                                          ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/01/21 17:42:33 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/12 12:44:21 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include <signals.h>
#include <core.h>

void	sigint_handler_main(int signum)
{
	g_signal |= signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	core_set_last_exit(130);
}

void	sigint_handler_heredoc(int signum)
{
	g_signal = (signum | HDOC_SIG_MASK);
	close(STDIN_FILENO);
	rl_on_new_line();
	rl_redisplay();
	write(1, "\n", 1);
	core_set_last_exit(130);
}

void	sigquit_handler_interactive(int signum)
{
	g_signal = signum;
	rl_on_new_line();
	rl_replace_line("", 0);
}

int	set_sig_handler(int signum, void (*fn)(int))
{
	struct sigaction	sig;

	sig.sa_handler = fn;
	sig.sa_flags = 0;
	sigemptyset(&sig.sa_mask);
	if (sigaction(signum, &sig, 0) == -1)
	{
		perror("sigaction");
		return (-1);
	}
	return (0);
}
