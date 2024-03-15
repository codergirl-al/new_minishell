/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:55:59 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/15 11:06:28 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib.h"

int ft_arrlen(char** arr);

char** ft_arrdup(char** arr)
{
    int len;
    char** new_arr;

    len = arrlen(arr);
    if (len == -1)
        return (NULL);
    new_arr = malloc(len * sizeof(char*));
    if (new_arr == NULL)
        return NULL;
    for (int i = 0; i < len; i++)
    {
        new_arr[i] = strdup(arr[i]);
        if (new_arr[i] == NULL)
        {
            for (int j = 0; j < i; j++)
                free(new_arr[j]);
            free(new_arr);
            return NULL;
        }
    }
    return (new_arr);
}
