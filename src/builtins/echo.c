/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:23:38 by apeposhi          #+#    #+#             */
/*   Updated: 2024/04/08 16:05:48 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	b_echo(char **cmds)
{
	bool	newline;
	int		start_index;
	int		i;

	newline = true;
	start_index = 1;
	if (cmds[1] && ft_strncmp(cmds[1], "-n", 2) == 0)
	{
		newline = false;
		start_index = 2;
	}
	i = start_index - 1;
	while (cmds[++i])
	{
		ft_putstr(cmds[i]);
		if (cmds[i + 1])
			ft_putchar(' ');
	}
	if (newline)
		ft_putchar('\n');
	return (0);
}
