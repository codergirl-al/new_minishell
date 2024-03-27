/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khnishou <khnishou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:59:07 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/27 02:08:53 by khnishou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib.h"

char	*ft_strjoin(char *s1, char *s2, int free_flag)
{
	char	*dest;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	dest = malloc(s1_len + s2_len + 1);
	if (dest == NULL)
		return (NULL);
	strcpy (dest, s1);
	strcpy (dest + s1_len, s2);
	if (free_flag & (1 << 0))
		free (s1);
	if (free_flag & (1 << 1))
		free (s2);
	return (dest);
}
