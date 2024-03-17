/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:14:56 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/17 19:20:44 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>

// int	ft_issep(char c)
// {
// 	return ((c == 32) || ((c >= 9) && (c <= 13)));
// }

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
			exe->cmd = malloc(sizeof(char *) * i + 1); /// protect
			exe->cmd[i] = NULL;
			return (0);
		}
		while (*str && !ft_issep(*str))
			str++;
		(void) parse_cmd(str, data, i, exe);	
		exe->cmd[i - 1] = start;
	}
	return (i);
}


// int main() {
// 	t_exec exe;
//     t_data data;

//     char *input = strdup("    1       2222222   \t \r    33333333    ");

//     parse_cmd(input, &data, 0, &exe);

// 	int i = 0;
// 	while (exe.cmd[i])
// 	{
// 		dprintf(2, "<%s>\n", exe.cmd[i]);
// 		i++;
// 	}
//     return 0;
// }
