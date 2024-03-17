/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:14:56 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/17 19:42:31 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>

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
