
#include "../include/minishell.h"
#include <stdio.h>
#include <string.h>

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
      *exp = ft_itoa(data->exit_status);
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
    *exp = ft_strdup(var + i);
    return (i);
  }
  return (0);
}

int dollar_handler(char **cont, t_data *data, int *len, int *it)
{
	char	*exp;
	int		i;

	it[1] = get_env(data->envp, (*cont) + it[0], &exp, data);
	i = it[0];
	if (it[1] != 1)
	{
		(*cont) = ft_swapstr((*cont), exp, it, STRFREE_SRC);
		it[0] = i;
		it[0] += ft_strlen(exp) - 1;
		*len += (-it[1]) + ft_strlen(exp);
		free(exp);
	}
	return (0);
}

int squote_handler(char **cont, int *it)
{
	int i;

	it[1] = iter_quotes((*cont) + it[0]) - ((*cont) + it[0]) + 1;
	i = it[0];
	(*cont) = ft_swapstr((*cont), ft_substr((*cont), it[0] + 1, it[1] - 2, 0), it, STRFREE_ARG | STRFREE_SRC);
	it[0] = i;
	it[0] += it[1] - 2;
	return (0);
}

int dquote_handler(char **cont, t_data *data, int *len, int *it)
{
	int i;

	it[1] = iter_quotes((*cont) + it[0]) - ((*cont) + it[0]) + 1;
	*len = it[1] + it[0] - 2;
	i = it[0];
	(*cont) = ft_swapstr((*cont), ft_substr((*cont), it[0] + 1, it[1] - 2, 0), it, STRFREE_ARG | STRFREE_SRC);
	it[0] = i;
	while ((*cont)[it[0]] && it[0] < *len)
	{
		if ((*cont)[it[0]] == '$')
			dollar_handler(cont, data, len, it);
		it[0]++; // check
	}
	return (0);
}