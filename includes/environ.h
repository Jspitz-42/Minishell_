/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ottomata <ottomata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:56:50 by ottomata          #+#    #+#             */
/*   Updated: 2025/03/08 20:53:28 by ottomata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_H
# define ENVIRON_H
# include <libft.h>
# include <vecarr.h>

t_vecarr	*setup(char **envp);
int			replace_env_value(char const *value);
char		*get_env_entry_from_key(char const *key);
long		get_env_index_from_key(char const *key);
int			remove_from_env_by_key(char const *key);
int			insert_env_kv_pair(char const *value);
#endif
