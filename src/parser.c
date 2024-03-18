#include "../include/minishell.h"

int parse_cmd(char *str, t_data *data, int it, t_exec *exe)
{
	char 	*start;
	int		i;

	i = it;
	if (str)
	{
		while (*str && ft_issep(*str))
			*(str++) = 0;
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
			str++;
		if (!parse_cmd(str, data, i, exe))
			return (0);
		exe->cmd[i - 1] = start;
	}
	return (i);
}
