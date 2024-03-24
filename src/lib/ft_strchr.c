/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 16:36:11 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/24 16:40:01 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib.h"

/**
 * Searches for the first occurrence of the character c (an unsigned char)
 * in the string pointed to by s. The terminating null character is considered
 * part of the string, so that if c is `\0', the function returns a pointer
 * to the terminator.
 *
 * @param s The string to be searched.
 * @param c The character to search for.
 * @return A pointer to the first occurrence of the character in the string,
 *         or NULL if the character is not found.
 */
char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return (char *)s;
		s++;
	}
	if (c == '\0')
		return (char *)s;
	return (NULL);
}
