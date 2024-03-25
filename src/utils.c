
#include "../include/minishell.h"
#include <stdio.h>

#define FLAG_D (1 << 0)
#define FLAG_S (1 << 1)

int cmdlen(char *str, int f_flag)
{
	int i;
	int len;
	int flag;

	flag = 0;
	i = 0;
	len = 0;
	if (str)
	{
		if (!f_flag && !(str[i] && ft_issep(str[i])))
		 	flag = 1;
		while (str[i])
		{
			while (str[i] && ft_issep(str[i]))
				i++;
			if (str[i] && !ft_issep(str[i]))
				len++;
			while (str[i] && !ft_issep(str[i]))
				i++;
		}
	}
	return (len - flag);
}

char *iter_quotes(char *str)
{
	int i;
	char c;

	i = 0;
	c = str[0];
	while (str[i] && (str[i] != c))
		i++;
	return (str + i);
}

char *get_env(char **env, char **str)
{
	char	*var;
	char	*var_name;
	int		i;

	i = 0;
	if ((*str) && env && *(*str) == '$')
	{
		(*str)++;
		while ((*str)[i] && ((*str)[i] != '\'' && (*str)[i] != '\"' && (*str)[i] != '$' && !ft_issep((*str)[i])))
			i++;
		var_name = ft_substr((*str), 0, i);
		*str += i - 1;
		var_name = ft_strjoin(var_name, "=", STRFREE_S1);
		var = ft_arrcmp((void **) env, var_name);
        if (!var)
            return (free(var_name), NULL);
        i = ft_strlen(var_name);
        free(var_name);
        return (var + i);
	}
    return (NULL);
}
