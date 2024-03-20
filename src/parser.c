
#include "../include/minishell.h"

#define IS_SQUOTE  (1 << 0)
#define IS_DQUOTE  (1 << 1)
#define IS_EXP     (1 << 2)


int redirect(char **str, t_exec *exe)
{
  if (str)
  {
    if(!strncmp("<", *str, 1))
      exe->fd_in = ft_open();// redirect in
    else if(!strncmp(">", *str, 1))
      exe->fd_out = ft_open();// redirect out
    else if(!strncmp("<<", *str, 2))
      exe->fd_in = ft_open();// heredoc
    else if(!strncmp(">>", *str, 2))
      exe->fd_out = ft_open();// redirect out append
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
    if (*str && !ft_issep(*str))
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
    while (*str && !ft_issep(*str))
    {
      if ((*str == '\'') || (*str == '\"'))
        str = iter_quotes(str);
      else if (*str == '$')
      {

        i += cmdlen(str);
      }
      // parsing
      str++;
    }
    if (!parse_cmd(str, data, i, exe))
      return (0);
    exe->cmd[i - 1] = start;
  }
  return (i);
}
