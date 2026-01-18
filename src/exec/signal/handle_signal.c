/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jspitz <jspitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:40:36 by jspitz            #+#    #+#             */
/*   Updated: 2025/02/20 12:40:32 by jspitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handle.h"

static void	ft_sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
}

static void	ft_sigquit_handler(int sig)
{
	(void)sig;
}

static void	ft_handle_eof(int sig)
{
	(void)sig;
	printf("\n");
	exit(0);
}

/*
brief: set up the signal for poti_shell, 
	  ft_sigint_handler / SIGINT for CTRL + C
	  		-> print a newline for now
			   maybe artficial potishell prompt
	  ft_sigquit_handler / SIGQUIT for CTRL + \
	  		-> rout the ctrl + \ to do nothing
				as ask in subject? need to check
	  ft_handle_eof / SIGTERM for Ctrl + D
	        -> exit minishell programm

no arg and no return value : full void function

STILL NOT TESTED
*/
void	ft_set_up_signal_handler(void)
{
	if (signal(SIGINT, ft_sigint_handler) == SIG_ERR)
	{
		perror("Error setting SIGINT handler");
		exit(1);
	}
	if (signal(SIGQUIT, ft_sigquit_handler) == SIG_ERR)
	{
		perror("Error setting SIGQUIT handler");
		exit(1);
	}
	if (signal(SIGTERM, ft_handle_eof) == SIG_ERR)
	{
		perror("Error setting EOF (Ctrl + D) handler");
		exit(1);
	}
}
