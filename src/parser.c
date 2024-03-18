/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:14:56 by ykerdel          #+#    #+#             */
/*   Updated: 2024/03/18 18:43:36 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
