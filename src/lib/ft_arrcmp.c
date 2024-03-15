/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:55:48 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/15 11:05:53 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib.h"

char *ft_arrcmp(void **arr, void *keyword)
{
    int    i;

    i = -1;
    while (arr[++i])
    {
        if (!ft_strncmp(keyword, arr[i], ft_strlen(keyword)))
            break;
    }
    return (arr[i]);
}
