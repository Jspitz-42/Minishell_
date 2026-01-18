/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   builtins.h                                           ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/01/15 12:27:38 by jspitz               │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/12 09:02:07 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <core.h>

/**
 * @brief : change current working directory
 * 
 * @param node struct with command data inside         
 */
void	ft_cd(t_subcmd *node);

/**
 * @brief : repeat any string given as argument
 *          followed by a new line. takes -n as option
 *          wich cancel new line print
 * @param ac : nummber of argument to print
 * @param av : all string to print + potential option
 * @param fd_out : file descriptor for potential redirection
 *                 set to stdout if = -1
 */
void	ft_echo(int ac, char **av, int fd_out);

/**
 * @brief : env with no option taken, display latest
 *          version of env variable
 * 
 * @param envp : actualized environnement variable
 * @param fd_out : potential redirection, set to stdout
 *                 if = -1
 */
void	ft_env(char **envp, int fd_out);

/**
 * @brief : exit the current process with a given status code
 *          still exit process even if invalid call of process         
 * 
 * @param ac : number of argument for error check
 * @param av : the string with exit status code
 * 
 * @return : given status code (wich = 2 if error)
 */
void	ft_exit(int ac, char **av);

/**
 * @brief : give the whole path to current working directory
 * 
 * @param fd_out : file descriptor to potiential redirection
 */
void	ft_pwd(int fd_out);

/**
 * @brief : erase a given variable from envp
 * 
 * @param var : the variable to unset
 */
void	ft_unset(const char *var);

/**
 * @brief : work in pair with ft_export, erase a pre existing
 *          variable pre set in envp before being replace by
 *          export command
 * @param var_name : the variable to erase,
 * 
 * @return : the index of the erased variable
 */
ssize_t	erase_from_envp(char const *var_name);

/**
 * @brief : add a variable to the environnement
 * 
 * @param var : the variable to add to envp, must 
 *              be in the format VAR=VALUE
 */
void	ft_export(char *var);
#endif
