/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 00:36:28 by apeposhi          #+#    #+#             */
/*   Updated: 2024/04/08 16:53:56 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib.h"

char	*my_strcat(char *dest, const char *src)
{
	char	*save;

	save = dest;
	while (*dest)
		dest++;
	while (*src != '\0')
		*dest++ = *src++;
	return (save);
}
