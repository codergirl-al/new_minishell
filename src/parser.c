/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khnishou <khnishou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:46:23 by khnishou          #+#    #+#             */
/*   Updated: 2024/03/27 14:46:27 by khnishou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <string.h>

#define IS_INOOUT  (1 << 0)
#define IS_DOUBLE   (1 << 1)

int ft_open(char *start, int len, int flag)
{
  int fd;
  char *file_name;

  fd = 0;
  file_name = ft_substr(start, 0, len, 0);
  if (!(flag & IS_INOOUT) && !(flag & IS_DOUBLE))
    fd = open(file_name, O_RDONLY);
  else if ((flag & IS_INOOUT) && !(flag & IS_DOUBLE))
    fd = open(file_name,O_RDWR | O_TRUNC | O_CREAT, 0000644);
  // else if (!(flag & IS_INOOUT) && (flag & IS_DOUBLE))
  //   fd = heredoc_handler(file_name);
  else if ((flag & IS_INOOUT) && (flag & IS_DOUBLE))
    fd = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0000644);
  if (fd == -1)
    perror("Minishell");
  return (fd);
}

int redirect(char **str, t_exec *exe)
{
  (void) exe;
  char *start;
  int flag;
  if (str && *str)
  {
    flag = 0;
    if(!strncmp(">", *str, 1))
      flag |= IS_INOOUT;
    if(!strncmp("<<", *str, 2) || !strncmp(">>", *str, 2))
      flag |= IS_DOUBLE;
    while (**str && (ft_issep(**str) || **str == '>' || **str == '<'))
      *(*str)++ = 0;
    // if (**str && !(ft_issep(**str) || **str == '>' || **str == '<'))
    // {
    start = *str;
    // }
    while (**str && !(ft_issep(**str) || **str == '>' || **str == '<'))
      (*str)++;
    if (flag & IS_INOOUT)
    {
      if (exe->fd_out > 0)
        close(exe->fd_out);
      exe->fd_out = ft_open(start, *str - start, flag);
    }
    else
    {
      if (exe->fd_in > 0)
        close(exe->fd_in);
      exe->fd_in = ft_open(start, *str - start, flag);
    }
  }
  return (0);
}

char *parse_arg(char **cont, t_data *data)
{
  int it[2] = {0, 0};
	int i;
	int len;
  char *exp;
  while ((*cont)[it[0]])
	{
    if ((*cont)[it[0]] == '\'')
    {
      it[1] = iter_quotes((*cont) + it[0]) - ((*cont) + it[0]) + 1;
			i = it[0];
			(*cont) = ft_swapstr((*cont), ft_substr((*cont), it[0] + 1, it[1] - 2, 0),  it, STRFREE_SRC | STRFREE_ARG);
			it[0] = i;
  	  it[0] += it[1] - 2;
    }
		else if ((*cont)[it[0]] == '\"')
		{
			it[1] = iter_quotes((*cont) + it[0]) - ((*cont) + it[0]) + 1;
			len = it[1] + it[0] - 2;
			i = it[0];
			(*cont) = ft_swapstr((*cont), ft_substr((*cont), it[0] + 1, it[1] - 2, 0),  it, STRFREE_SRC | STRFREE_ARG);
			it[0] = i;
			while ((*cont)[it[0]] && it[0] < len)
			{
				if ((*cont)[it[0]] == '$')
				{
					it[1] = get_env(data->envp, (*cont) + it[0], &exp);
					i = it[0];
					if (it[1] != 1)
					{
						(*cont) = ft_swapstr((*cont), exp, it, STRFREE_SRC);
            it[0] = i;
            it[0] += ft_strlen(exp) - 1;
            len += (-it[1]) + ft_strlen(exp);
					}
				}
				it[0]++;
			}
		}
    else if ((*cont)[it[0]] == '$') // value doesn t exist
    {
      it[1] = get_env(data->envp, (*cont) + it[0], &exp);
      i = it[0];
      if (it[1] != 1)
      {
        (*cont) = ft_swapstr((*cont), exp, it, STRFREE_SRC);
        it[0] = i;
        it[0] += ft_strlen(exp) - 1;
        len += (-it[1]) + ft_strlen(exp);
      }
      // creat a list
    }
    it[0]++; // echo "111"'2222'
  }
  return ((*cont));
}

t_list *set_arg(t_data *data, char *str, t_list *old, bool exp_flag)
{
  t_list *new;
  char *cont;

  cont = strdup(str);
  if (!cont)
    return (NULL);
  if (exp_flag)
    parse_arg(&cont, data);
  new = ft_lstnew((void *) cont);
  if (!new)
    return (NULL);
  new->next = old;
  return (new);
}

t_list *parse_cmd(char *str, t_data *data, t_exec *exe, bool exp_flag) {
  char *start;
  t_list  *new;
  t_list  *old;

  new = NULL;
  if (str) {
    while (*str && (ft_issep(*str) || *str == '>' || *str == '<'))
    {
      if ((*str == '<') || (*str == '>'))
        redirect(&str, exe);
      else
        *(str++) = 0;
    }
    if (*str && !(ft_issep(*str) || *str == '>' || *str == '<'))
      start = str;
    else
      return (NULL);
    while (*str && !(ft_issep(*str) || *str == '>' || *str == '<'))
        str++;
    old = parse_cmd(str, data, exe, exp_flag);
    new = set_arg(data, start, old, exp_flag);
    if (!new)
      return (NULL);
  }
  return (new);
}
