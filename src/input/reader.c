/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   reader.c                                             ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/01/21 17:39:20 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/17 16:29:47 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <input.h>
#include <pipe_exec.h>

static bool	pre_check(t_cmd *cmd, char **envp)
{
	if (cmd->subs == NULL)
	{
		ft_dprintf(2, "potishell: '' Command not found\n");
		return (false);
	}
	if (!cmd || !check_all_builtins(cmd, envp) || !check_all_command(cmd)
		|| !check_all_files(cmd))
	{
		core_set_last_exit(127);
		return (false);
	}
	return (true);
}

static void	set_up_exec(char *input, char **envp)
{
	t_subcmd	*scmd;
	t_cmd		*cmd;
	t_list		*iter;

	cmd = NULL;
	scmd = NULL;
	iter = NULL;
	if (ft_strlen(input) > 0)
		cmd = command_from_user_input(input);
	if (scanner()->encountered_error)
	{
		core_set_last_exit(2);
		return ;
	}
	if (cmd && cmd->subs != NULL)
		iter = cmd->subs;
	if (cmd && cmd->cmdc >= 256)
		ft_dprintf(2, "too many commands\n");
	else if (ft_strlen(input) > 0 && pre_check(cmd, envp))
		cmd_pipex(cmd, core_envp(), iter, scmd);
}

void	readline_wrapper(char **envp)
{
	char	*input;
	char	*tmp;

	while (1)
	{
		g_signal = 0;
		set_sig_handler(SIGQUIT, SIG_IGN);
		tmp = readline(CYAN STR_PROMPT DEFAULT);
		if (!tmp)
			break ;
		input = ftgc_strdup(tmp);
		free(tmp);
		add_history(input);
		set_up_exec(input, envp);
		gc_free(input);
	}
	rl_clear_history();
	gc_clear();
}
