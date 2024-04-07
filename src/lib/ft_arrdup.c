/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:55:59 by apeposhi          #+#    #+#             */
/*   Updated: 2024/04/07 19:23:30 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib.h"

char	**ft_arrdup(char **arr)
{
	char	**new_arr;
	int		len;
	int		it;

	len = ft_arrlen(arr);
	if (len == -1)
		return (NULL);
	new_arr = malloc((len + 1) * sizeof(char *));
	if (new_arr == NULL)
		return (NULL);
	it = -1;
	while (arr[++it])
	{
		new_arr[it] = ft_strdup(arr[it]);
		if (new_arr[it] == NULL)
		{
			while (it >= 0)
				free(new_arr[it--]);
			free(new_arr);
			return (NULL);
		}
	}
	new_arr[it] = NULL;
	return (new_arr);
}
