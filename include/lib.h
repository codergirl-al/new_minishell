/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:10:15 by apeposhi          #+#    #+#             */
/*   Updated: 2024/04/08 00:46:27 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include <limits.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

# define STRFREE_SRC 1
# define STRFREE_ARG 2
# define STRFREE_S1 1
# define STRFREE_S2 2

int		ft_issep(char c);
int		ft_isalnum(int c);
int		ft_istoken(char c);
int		ft_isalpha(int c);
int		ft_isbuiltin(t_list *lst);

int		ft_arrlen(char **arr);
char	*ft_arrcmp(void **arr, void *keyword);
char	**ft_arrdup(char **arr);
void	ft_arrfree(char **arr);

size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
char	*ft_substr(char *str, unsigned int start, size_t len, int free_flag);
char	*ft_swapstr(char *src, char *swap, int *ints, int free_flag);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2, int free_flag);
char	*ft_itoa(int n);
char	*my_strcpy(char *dest, const char *src);
char	*my_strcat(char *dest, const char *src);

t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
char	**lst_to_arr(t_list *head);
void	ft_lstfree(t_list *lst);

void	ft_putstr_fd(char *s, int fd);

int		ft_setflag(int flag, ...);
int		ft_unsetflag(int flag, ...);

#endif
