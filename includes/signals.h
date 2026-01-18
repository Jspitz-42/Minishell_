/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ottomata <ottomata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:42:58 by tblochet          #+#    #+#             */
/*   Updated: 2025/03/08 20:41:44 by ottomata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

enum		e_signal_masks
{
	HDOC_SIG_MASK = 1 << 16,
	FORK_SIG_MASK = 1 << 17,
};

extern int	g_signal;

/**
 * @brief Assign FN as a handler for signal SIGNUM
 * @param signum Signal number to handle
 * @param fn Handler function
 * @return Status code, < 0 in case of error
 */
int			set_sig_handler(int signum, void (*fn)(int));

/**
 * @brief Specific handler for SIGINT in a heredoc
 */
void		sigint_handler_heredoc(int signum);

/**
 * @brief Main handler for SIGINT
 */
void		sigint_handler_main(int signum);

/**
 * @brief Main handler for SIGQUIT
 */
void		sigquit_handler_interactive(int signum);
#endif
