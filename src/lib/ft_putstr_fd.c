/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 22:19:02 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/18 22:27:36 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib.h"

/*
** @brief Write a string to the given file descripter.
**
** @param str:  a NULL-terminated string
** @param fd: the file descripter
*/
void ft_putstr_fd(char *s, int fd)
{
	size_t i;

	i = 0;
	if (!s)
		return;
	while (i < ft_strlen(s)) 
	{
		write(fd, &s[i], 1);
		i++;
	}
}
