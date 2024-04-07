/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swapstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 19:27:49 by ykerdel           #+#    #+#             */
/*   Updated: 2024/04/07 19:28:12 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib.h"

static void	ft_free(char *src, char *arg, int free_flag)
{
	if (free_flag & STRFREE_SRC)
	{
		free(src);
	}
	if (free_flag & STRFREE_ARG)
	{
		free(arg);
	}
}

char	*ft_swapstr(char *src, char *swap, int *ints, int free_flag)
{
	int		i;
	char	*res;
	int		end;
	int		src_len;

	src_len = ft_strlen(src);
	if (!src || ints[0] >= src_len)
		return (NULL);
	end = ints[0] + ints[1];
	res = malloc(src_len - ints[1] + ft_strlen(swap) + 1);
	if (!res)
		return (NULL);
	i = -1;
	while (++i < (int) ints[0])
		res[i] = src[i];
	ints[0] = 0;
	if (swap)
		while (swap[ints[0]])
			res[i++] = swap[ints[0]++];
	while (src[end])
		res[i++] = src[end++];
	res[i] = '\0';
	ft_free(src, swap, free_flag);
	return (res);
}
