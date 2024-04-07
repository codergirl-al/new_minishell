/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:25:14 by apeposhi          #+#    #+#             */
/*   Updated: 2024/04/08 00:05:41 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	my_atoi(const char *str, int *out)
{
	int	result;
	int	sign;
	int	digit;

	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	result = 0;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		digit = *str - '0';
		if (result > (INT_MAX - digit) / 10)
			return (-1);
		result = result * 10 + digit;
		str++;
	}
	*out = result * sign;
	return (0);
}

int	b_exit(char **args)
{
	int	status;

	if (args[1] && args[2])
	{
		fprintf(stderr, "exit: too many arguments\n");
		return (1);
	}
	printf("exit\n");
	if (args[1])
	{
		if (my_atoi(args[1], &status) == -1)
		{
			fprintf(stderr, "exit: %s: numeric argument required\n", args[1]);
			return (2);
		}
		else
			return (status);
	}
	return (0);
}
