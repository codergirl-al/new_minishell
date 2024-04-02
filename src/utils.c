
#include "../include/minishell.h"
#include <stdio.h>

#define FLAG_D (1 << 0)
#define FLAG_S (1 << 1)

char *iter_quotes(char *str) {
  int i;
  char c;

  i = 1;
  c = str[0];
  while (str[i] && (str[i] != c))
    i++;
  return (str + i);
}

int get_env(char **env, char *str, char **exp, t_data *data) {
  char *var;
  char *var_name;
  int i;

  i = 0;
  *exp = NULL;
  if (str && env && *str == '$') {
    str++;
    if (str[i] && str[i] == '?') {
      *exp = ft_itoa(data->exit_status); // check leaks
      return (2);
    }
    while (str[i] && (str[i] != '\'' && str[i] != '\"' && str[i] != '$' &&
                      !ft_issep(str[i])))
      i++;
    var_name = ft_substr(str, 0, i, 0);
    str += i - 1;
    i++;
    var_name = ft_strjoin(var_name, "=", STRFREE_S1);
    var = ft_arrcmp((void **)env, var_name);
    if (!var)
      return (free(var_name), i);
    free(var_name);
    *exp = var + i;
    return (i);
  }
  return (0);
}
