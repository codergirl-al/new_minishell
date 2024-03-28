/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:23:38 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/28 20:33:05 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	b_echo(char **cmds)
{
	bool	newline;
	int		arrlen;
	int		start_index;
	int		i;

	arrlen = 0;
	newline = true;
	start_index = 1;
	if (cmds[1] && ft_strncmp(cmds[1], "-n", 2) == 0)
	{
		newline = false;
		start_index = 2;
	}
	while (cmds[arrlen])
		arrlen++;
	i = start_index - 1;
	while (cmds[++i])
	{
		fputs(cmds[i], stdout);
		if (i < arrlen - 1)
			putchar(' ');
	}
	if (newline)
		putchar('\n');
}
