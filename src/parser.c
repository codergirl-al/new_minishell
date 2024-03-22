
#include "../include/minishell.h"

#define IS_INOOUT  (1 << 0)
#define IS_DOUBLE   (1 << 1)

int ft_open(char *start, int len, int flag)
{
  int fd;
  char *file_name;

  file_name = ft_substr(start, 0, len);
  if (!(flag & IS_INOOUT) && !(flag & IS_INOOUT))
    fd = open(file_name, O_RDONLY);
  else if ((flag & IS_INOOUT) && !(flag & IS_INOOUT))
    fd = open(file_name,O_RDWR | O_TRUNC | O_CREAT, 0000644);
  // else if (!(flag & IS_INOOUT) && (flag & IS_INOOUT))
  //   fd = heredoc_handler(file_name);
  else if ((flag & IS_INOOUT) && (flag & IS_INOOUT))
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
