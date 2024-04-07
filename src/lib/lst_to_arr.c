/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 18:57:24 by ykerdel           #+#    #+#             */
/*   Updated: 2024/04/07 18:58:08 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib.h"

char	**lst_to_arr(t_list *head)
{
	int		size;
	char	**arr;
	int		it;

	it = 0;
	size = ft_lstsize(head);
	if (size == 0)
		return (NULL);
	arr = (char **)malloc((size + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (head)
	{
		arr[it] = head->content;
		head = head->next;
		it++;
	}
	arr[it] = NULL;
	return (arr);
}
