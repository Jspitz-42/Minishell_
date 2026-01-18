/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ottomata <ottomata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 07:16:06 by tblochet          #+#    #+#             */
/*   Updated: 2025/03/08 20:00:57 by ottomata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <libft.h>
# include <stdio.h>

/**
 * @brief Get the position of C in S as an integer
 * @param s String to look into
 * @param c Char to search for
 * @return The position of C or -1 if not found.
 */
int		index_of(char *s, char c);

/**
 * @brief Replaces WHAT with WITH in the null-terminated string IN
 * @param in Target string
 * @param what Substring to replace
 * @param with Replacement
 * @return A newly malloc'd string with WHAT replaced by WITH or NULL in case of
 * error
 */
char	*replace(char *in, char *what, char *with);

/**
 * @brief Frees a pointer to pointers and the pointed pointers
 * @param ptr Pointer of pointers to free
 */
void	free_2d(void **ptr);

/**
 * @brief Frees a pointer to pointers and the pointed pointers
 * Thosee pointers are free'd with gc_free
 * @param ptr Pointer of pointers to free
 */
void	gc_free_2d(void **ptr);

#endif
