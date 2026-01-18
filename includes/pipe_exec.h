/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jspitz <jspitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:55:21 by jspitz            #+#    #+#             */
/*   Updated: 2025/03/15 15:37:06 by jspitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_EXEC_H

# define PIPE_EXEC_H

# include <errno.h>
# include <fcntl.h>
# include <lexer.h>
# include <libft.h>
# include <parser.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stddef.h>

/**
 * @brief : monitor the execution of a command line using given
 *          and updated ENVP environnement variable.
 * 
 * @param cmd : Main struct with all input information 
 * 					from readline wrapper
 * @param envp : environnement of the program
 * @param iter : t_list with void param use to navigate through
 * 			     t_cmd and t_subcmd struct content
 * @param scmd : a node with information about one pipe of a command
 * 			     line
 */
void	cmd_pipex(t_cmd *cmd, char **envp, t_list *iter, t_subcmd *scmd);

/**
 * @brief : check if cmd is builtins
 * 
 * @param argv : cmd name
 * 
 * @return : true if builtin | false if not
 */
int		is_blt(char *argv);

/**
 * @brief : execute builtins from the mighty potishell
 * 
 * @param node : struct with cmd info inside
 * @param envp : environemment of the programm
 * @param argv : array with cmd + arg
 */
void	exec_builtins(t_cmd *cmd, t_subcmd *node, char *argv[256], int *fds);

/**
 * @brief : fill array with cmd list content
 * 
 * @param argv : array getting filled
 * @param node : struct with cmd + arg inside
 * 
 * @return the array filled
 */
char	**build_argv(char **argv, t_subcmd *node);

/**
 * @brief : execute the command within a node from a pipe
 * 			check if this command exist, is a builtin
 * 			of if jose bove is still beautifull
 * 
 * @param node : node from a pipe with data to execute
 * 			     a command
 * @param envp : potishell environnement 
 */
void	execute(t_cmd *cmd, t_subcmd *node, char **envp, int *fds);

/**
 * @brief : error exit function with custom message for perror
 * 			+ custom status
 * @param s : perror message
 * @param status : exit status code
 */
void	ft_exec_exit(char *s, int status);

/**
 * @brief : this function wait for all child process
 * 			to die before quit pipe main function
 * 
 * @param pid : array of child proces pid waiting to die 
 * 				like me when I drop coffe on my chair, help
 * @param i : pid array index
 */
void	wait_all_pid(int *pid, int i);

/**
 * @brief : close used fd from pipe command and advance to the next next
 *
 * @param iter : use to check if end of pipe or not
 * @param cmd : main struct with all input information inside
 *                  here we use the pipe[2] in
 * @param scmd : current node of the pipe
 * @param b_fd : file_descriptor of previous pipe node
 * */
void	cls_scmd_fd(t_list **iter, t_cmd *cmd, t_subcmd *scmd, int *b_fd);

/**
 * @brief : open redirection file descriptor if necessary
 *          + change flag depending of append mode.
 *
 * @param in_fd : pointer to a small fds[3] array of file descriptor
 * @param out_fd : same for out_file descriptor in fds[3]
 * @param scmd : current node of the pipe
 */
void	set_up_redir(int *in_fd, int *out_fd, t_subcmd *scmd);

/**
 * @brief : out of pipe, shell builtins must be executed in the parent process
 *          this functions execute builtins function without forking
 * 
 * @param node : hold data about current command
 * @param fdo : potential redirection | set to 1 if -1
 */
void	exec_builtins_out_pipe(t_subcmd *node, int fdo);

/**
 * @brief : set up the stdin dup2 within a succession of pipe
 *          + dup2 error management;
 *`
 * @param in_fd_redir : redirection file descriptor
 * @param before_fd : read entry of pipe
 */
void	set_up_stdin(int *before_fd, int *in_fd_redir);

/**
 * @brief: set up the stdout dup2 within a succesion of pipe
 *         + dup2 error management
 *
 * @param iter : t_list to check if last node of pipe
 * @param command : main structur with all input line data inside
 *                  here we use the pipe[2] within
 * @param out_fd_redir : outfile file descriptor to prioritiz redirection
 */
void	set_up_stdout(t_list *iter, t_cmd *command, int *out_fd_redir);

/**
 * @brief : check if relatative/absolute given command is executable
 * 
 * @param cmd : hold all data from given input
 * 
 * @return : the full command if executable | NULL + error msg if not
 */
char	*relative_absolute_command(char const *cmd);

/**
 * @brief : send executable (./something) directly to
 *          execve and skip useless built of path
 * 
 * @param argv : executable + arg send to it
 * @param envp : environnement variable
 */
void	execute_relative(char **argv, char **envp);

/**
 * @brief : in case of execve failures, clear input and free
 *          potiential memory alloc
 * 
 * @param path : built path to command to potentialy free
 */
void	error_execve(char *path);

/**
 * @brief : norm necessary function, take previously set
 *          and double checked data and give them
 *          to execve function.
 * 
 * @param path : fully built path to command
 * @param argv : command + all potential arg
 * @param envp : actualized environement variable
 */
void	execute_end(char *path, char **argv, char **envp);

/**
 * @brief : check if all non-builtins command are 
 *          executable
 * 
 * @param cmd : hold all data about current input
 * 
 * @return : true if all non builtins are executable
 *           | false if not
 */
bool	check_all_command(t_cmd *cmd);

/**
 * @brief : last check before send the input to exec
 *          check if all redirections are functionnal
 * 
 * @param cmd : hold all data about current input
 * 
 * @return : true if redir are ok | false if not
 */
bool	check_all_files(t_cmd *cmd);

/**
 * @brief : check if unset is executable
 * 
 * @param  node : hold  all data about current command
 * 
 * @return : true if unset is executable | false if not 
 */
bool	check_unset(t_subcmd *node);

/**
 * @brief : check if pwd is executable
 * 
 * @param node : hold all data about current command
 * 
 * @return : true if pwd is executable | false if not
 */
bool	check_pwd(t_subcmd *node);

/**
 * @brief : check if export command is executable
 * 
 * @param node : hold all data about current command
 * 
 * @return : true if export is executable | false if not
 */
bool	check_export(t_subcmd *node);

/**
 * @brief : check if env command is executable
 * 
 * @param envp : environnement variable
 * 
 * @return : true if env is executable | false if not
 */
bool	check_env(char **envp);

/**
 * @brief : check if cd will be executable
 * 
 * @param node : hold all data about current command
 * 
 * @return : true if executable | false if not
 */
bool	check_cd(t_subcmd *node);

/**
 * @brief : check all builtins command inside cmd
 *          return false if one of them is not executable
 *          + display error message for each
 * @param cmd : the main data struct with all input data parsed
 * @param envp : environnement variable
 * 
 * @return : false if error | true if no error
 */
bool	check_all_builtins(t_cmd *cmd, char **envp);

#endif
