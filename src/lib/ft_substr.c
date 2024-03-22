/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khnishou <khnishou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:59:07 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/22 01:44:59 by khnishou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib.h"

static unsigned int	tt_strlcpy(char *dest, const char *src, double size)
{
	unsigned int	i;
	unsigned int	lsrc;

	size = size + 1;
	lsrc = 0;
	while (src[lsrc] != '\0')
		lsrc++;
	if (size > 0)
	{
		i = 0;
		while (i < size - 1 && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (lsrc);
}

char	*ft_substr(char *str, unsigned int start, size_t len)
{
	char	*dest;
	size_t	size;
    
	if (start >= ft_strlen (str))
		return (strdup (""));
	else if (ft_strlen(str) - start < len)
		size = ft_strlen(str) - start;
	else
		size = len;
	dest = malloc(sizeof(char) * size + 1);
    if (!dest)
	{
        return (NULL);
	}
	tt_strlcpy(dest, str + start, len);
	return (dest);
}
