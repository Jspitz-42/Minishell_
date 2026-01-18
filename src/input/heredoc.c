/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   heredoc.c                                            ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/01/21 17:46:42 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/12 13:40:30 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

static char	*join(char *sep, char **arr)
{
	char	*joint;
	char	*tmp;
	size_t	i;

	i = 0;
	if (!arr)
		return (0);
	joint = ft_strdup("");
	if (!joint)
		return (0);
	while (arr[i])
	{
		tmp = ft_strjoin(joint, arr[i]);
		free(joint);
		if (arr[i + 1])
			joint = ft_strjoin(tmp, sep);
		else
			joint = ft_strdup(tmp);
		free(tmp);
		i++;
	}
	return (joint);
}

static int	hd_inner_loop(int fd, char *limiter, char *prompt)
{
	char	*input;
	int		bytes;

	bytes = 0;
	while (1)
	{
		input = readline(prompt);
		if (!input)
		{
			bytes = -1;
			if (!(g_signal & HDOC_SIG_MASK))
				ft_dprintf(2,
					"potishell: warning: got <CTRL+D> instead of '%s'.\n",
					limiter);
			break ;
		}
		if (ft_strcmp(input, limiter) == 0)
			break ;
		else
			bytes += (int)ft_putendl_fd(input, fd);
		free(input);
	}
	free(input);
	return (bytes);
}

int	heredoc(int fd, char *limiter)
{
	char		*prompt;
	int			bytes;
	int			free_prompt;
	const char	*parr[] = {RED STR_HEREDOC DEFAULT, limiter, "> ", 0};

	set_sig_handler(SIGINT, &sigint_handler_heredoc);
	prompt = join(" ", (char **)parr);
	free_prompt = 1;
	if (!prompt)
	{
		prompt = YELLOW STR_HEREDOC DEFAULT "> ";
		free_prompt = 0;
	}
	bytes = hd_inner_loop(fd, limiter, prompt);
	if (free_prompt)
		free(prompt);
	set_sig_handler(SIGINT, &sigint_handler_main);
	close(fd);
	return (bytes);
}
