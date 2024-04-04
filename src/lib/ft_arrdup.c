/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:55:59 by apeposhi          #+#    #+#             */
/*   Updated: 2024/04/04 14:27:12 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib.h"

char **ft_arrdup(char **arr) {
  char **new_arr;
  int len;
  int i;
  int j;

  len = ft_arrlen(arr);
  if (len == -1)
    return (NULL);
  new_arr = malloc(len * sizeof(char *));
  if (new_arr == NULL)
    return (NULL);
  i = -1;
  while (arr[++i]) {
    new_arr[i] = ft_strdup(arr[i]);
    if (new_arr[i] == NULL) {
      j = -1;
      while (++j < i)
        free(new_arr[j]);
      free(new_arr);
      return (NULL);
    }
  }
  new_arr[i] = NULL;
  return (new_arr);
}
