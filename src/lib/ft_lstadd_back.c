/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 21:00:17 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/15 10:56:50 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib.h"

/*
** @brief append a node to a linked list.
**
** @param lst:  the memory address of the pointer pointing
** to the start of linked list.
** @param back: the node to be appended
*/
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lista;

	if (lst)
	{
		if (*lst)
		{
			lista = ft_lstlast(*lst);
			lista -> next = new;
		}
		else
			*lst = new;
	}
}
