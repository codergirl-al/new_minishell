/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:10:15 by apeposhi          #+#    #+#             */
/*   Updated: 2024/04/04 13:51:25 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include <limits.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define STRFREE_S1 (1 << 0)
# define STRFREE_S2 (1 << 1)

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

#define STRFREE_SRC (1 << 0)
#define STRFREE_ARG (1 << 1)
#define STRFREE_S1 (1 << 0)
#define STRFREE_S2 (1 << 1)

int		ft_issep(char c);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_arrlen(char **arr);
char	*ft_arrcmp(void **arr, void *keyword);
char	**ft_arrdup(char **arr);
char	*ft_strjoin(char *s1, char *s2, int free_flag);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_substr(char *str, unsigned int start, size_t len, int free_flag);
char	*ft_swapstr(char *src, char *swap, int *ints, int free_flag);

t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
char	**lst_to_arr(t_list *head);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_itoa(int n);
void	ft_lstfree(t_list *lst);
void	ft_arrfree(char **arr);

#endif
