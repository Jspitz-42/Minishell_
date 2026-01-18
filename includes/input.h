/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   input.h                                              ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/01/21 17:39:48 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/12 12:48:24 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H
# include <readline/history.h>
# include <readline/readline.h>
# include <libft.h>
# include <stdio.h>
# include <signals.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <utils.h>
# include <lexer.h>
# include <parser.h>
# include <defines.h>

/**
 * @brief Gets user input for the content of a heredoc
 * @param fd Target FD to write the content to.
 * @param limiter Limiter for when to stop recording user input
 * @return Written bytes count or -1 in case of error.
 */
int		heredoc(int fd, char *limiter);

/**
 * @brief Wrapper for readline, used to parse a user input.
 * @param envp Pointer to the array of null-terminated strings representing
 * the environment variables.
 */
void	readline_wrapper(char **envp);

/**
 * @brief : close fd array use to saved STD_IN and STD_OUT
 * 
 * @param fds : array of fd use to saved STD_IN and STD_OUT
 */
void	close_saved_fd(int *fds);

#endif
