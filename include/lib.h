/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khnishou <khnishou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:10:15 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/25 01:35:54 by khnishou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

#include <stdlib.h>
#include <string.h>

typedef	struct	s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

#define STRFREE_S1 (1 << 0)
#define STRFREE_S2 (1 << 1)

int		ft_issep(char c);
int		ft_arrlen(char **arr);
char	*ft_arrcmp(void **arr, void *keyword);
char	**ft_arrdup(char **arr);
char	*ft_strjoin(char *s1, char *s2, int free_flag);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_substr(char *str, unsigned int start, size_t len);

t_list	*ft_lstnew(void *content);

#endif