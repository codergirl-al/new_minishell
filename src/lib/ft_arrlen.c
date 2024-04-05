/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khnishou <khnishou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:56:06 by apeposhi          #+#    #+#             */
/*   Updated: 2024/04/05 17:01:53 by khnishou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib.h"

int	ft_arrlen(char **arr)
{
	int	it;

	it = -1;
	if (arr)
		while (arr[++it])
			;
	return (it);
}
