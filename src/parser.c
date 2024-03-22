
#include "../include/minishell.h"
#include <stdio.h>

#define IS_INOOUT  (1 << 0)
#define IS_DOUBLE   (1 << 1)


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
    if (**str && !(ft_issep(**str) || **str == '>' || **str == '<'))
    {
      start = *str;
    }
    while (**str && !(ft_issep(**str) || **str == '>' || **str == '<'))
      (*str)++;
    if (flag & IS_INOOUT)
      exe->fd_out = ft_open(start, *str - start, flag);
    else
      exe->fd_in = ft_open(start, *str - start, flag);
  }
  return (0);
}

int parse_cmd(char *str, t_data *data, int it, t_exec *exe) {
  char *start;
  int i;

  i = it;
  if (str) {
    while (*str && (ft_issep(*str) || *str == '>' || *str == '<'))
    {
      if (((*str == '<') || (*str == '>')) && redirect(&str, exe))
        return (0);
      *(str++) = 0;
    }
    if (*str && !(ft_issep(*str) || *str == '>' || *str == '<'))
    {
      start = str;
      i++;
    }
    else
    {
      exe->cmd = malloc(sizeof(char *) * i + 1);
      if (!exe->cmd)
        return (0);
      exe->cmd[i] = NULL;
      return (i);
    }
    while (*str && !(ft_issep(*str) || *str == '>' || *str == '<'))
    {
      // if ((*str == '\'') || (*str == '\"'))
      //   str = iter_quotes(str);
      // else if (*str == '$')
      // {

      //   i += cmdlen(str);
      // }
      // parsing
      str++;
    }
    if (!parse_cmd(str, data, i, exe))
      return (0);
    exe->cmd[i - 1] = start;
  }
  return (i);
}
