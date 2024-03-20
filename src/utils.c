
#include "../include/minishell.h"

#define FLAG_D (1 << 0)
#define FLAG_S (1 << 1)

int cmdlen(char *str)
{
	int i;
	int len;

	i = 0;
	len = 0;
	if (str)
	{
		while (str[i])
		{
			if (ft_issep(str[i]))
				len++;
			while (str[i] && ft_issep(str[i]))
				i++;
			while (str[i] && !ft_issep(str[i]))
				i++;
		}
	}
	return (len);
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

char *get_env(char **env, char *var_name)
{
	char	*var;

	var = NULL;
	if (var_name && env)
	{
		var_name = ft_strjoin(var_name, "=", 0);
		var = ft_arrcmp((void **) env, var_name);
		free(var_name);
	}
	if (!var)
		return (NULL);
	return (var + ft_strlen(var_name));
}
