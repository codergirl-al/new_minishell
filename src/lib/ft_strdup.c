/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 19:08:33 by ykerdel           #+#    #+#             */
/*   Updated: 2024/04/07 19:08:42 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib.h"

static void	*tt_memcpy(void *restrict dest, const void *restrict src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	if (!dest && !src)
		return (0);
	i = 0;
	d = (char *)dest;
	s = (char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}

char	*ft_strdup(const char *s)
{
	char	*d;
	size_t	len;

	len = ft_strlen(s) + 1;
	d = malloc (len);
	if (d == NULL)
		return (NULL);
	d = tt_memcpy (d, s, len);
	return (d);
}
