/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:25:14 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/19 17:29:45 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <errno.h>

static int my_atoi(const char *str, int *out)
{
    int result = 0;
    int sign = 1;

    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }
	while (*str)
	{
        if (*str < '0' || *str > '9') {
            return -1;
        }
        int digit = *str - '0';

        if (result > (INT_MAX - digit) / 10)
            return -1;
        result = result * 10 + digit;
		str++;
    }

    *out = result * sign;
    return 0;
}


void	b_exit(char **args)
{
	int	exit_status;

	exit_status = 0;
	if (args[1] && args[2])
	{
        fprintf(stderr, "exit: too many arguments\n");
        return ;
    }
    if (args[1])
	{
        if (!safe_atoi(args[1], &exit_status))
		{
            fprintf(stderr, "exit: %s: numeric argument required\n", args[1]);
            exit_status = 2;
        }
    }
    exit(exit_status);
}
