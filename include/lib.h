/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:10:15 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/18 23:08:48 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int		ft_issep(char c);
int		ft_arrlen(char **arr);
char	*ft_arrcmp(void **arr, void *keyword);
char	**ft_arrdup(char **arr);
char	*ft_strjoin_01(char *s1, char *s2);
char	*ft_strjoin_11(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);

#endif