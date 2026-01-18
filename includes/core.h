/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ottomata <ottomata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:59:48 by tblochet          #+#    #+#             */
/*   Updated: 2025/03/08 20:27:55 by ottomata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H
# include <libft.h>
# include <parser.h>
# include <sys/wait.h>
# include <unistd.h>
# include <vecarr.h>
# define ENV_MAX_VARS 256
# define ENV_VAR_MAX_LEN 4096

typedef struct s_core		t_core;
typedef struct s_env_entry	t_var;

/**
 * @brief Inner working of the shell
 */
struct						s_core
{
	t_list					*commands;
	t_vecarr				*env;
	int						last_exit;
	int						init_ok;
};

/**
 * @brief Singleton of the s_core struct
 *
 * @return Pointer to the core instance.
 */
t_core						*core(void);

/**
 * @brief Sets the last_exit field of the core
 *
 * @param status Status to set
 * @return The set status.
 */
int							core_set_last_exit(int status);

/**
 * @brief Retrieves the value of an environment variable from the core's envp
 * @param name Variable name
 * @return Value for NAME, or NULL is name was not found.
 */
char						*core_getenv(char *name);

char						*core_envp_as_string(void);

char						**core_envp(void);
#endif
