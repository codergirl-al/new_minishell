/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:06:04 by apeposhi          #+#    #+#             */
/*   Updated: 2024/04/03 16:23:20 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib.h"

/*
** @param str: a NULL-terminated string
** @return the length of the given string
*/
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s)
		while (s[i] != '\0')
			i++;
	return (i);
}
