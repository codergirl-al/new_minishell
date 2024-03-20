/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:10:15 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/18 17:46:22 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

#include <stdlib.h>
#include <string.h>

#define STRFREE_S1 (1 << 0)
#define STRFREE_S2 (1 << 1)

int		ft_issep(char c);
int		ft_arrlen(char **arr);
char	*ft_arrcmp(void **arr, void *keyword);
char	**ft_arrdup(char **arr);
char	*ft_strjoin(char *s1, char *s2, int free_flag);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);


#endif