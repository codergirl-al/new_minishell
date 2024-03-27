/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:23:38 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/27 13:06:17 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	safe_write(int fd, const char *buf, size_t count)
{
	size_t	written;

	written = write(fd, buf, count);
	if (written == -1 || (size_t)written != count)
		return (handle_error(1, "minishell: echo: write error"));
	return (0);
}

int	b_echo(char **args)
{
	bool	newline;
	int		i;

	newline = true;
	i = 1;
	if (args[i] && strcmp(args[i], "-n") == 0)
	{
		newline = false;
		i++;
	}
	while (args[i])
	{
		if (safe_write(STDOUT_FILENO, args[i], strlen(args[i])))
			return (1);
		if (args[i + 1])
			if (safe_write(STDOUT_FILENO, " ", 1))
				return (1);
		i++;
	}
	if (newline)
		if (safe_write(STDOUT_FILENO, "\n", 1))
			return (1);
	return (0);
}
