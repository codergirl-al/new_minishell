/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 20:47:49 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/15 13:00:36 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int parse_cmd(char ***arr, char *str) /// we do it together
// {
// }

// int action(char *cmd, int type)
// {
// }

int	ft_parse_input(char *input, t_list	lst)
{
	char	*start;
	char	*end;

	start = input;
	end = input;
	while (input && *end != '\0')
	{
		if (*end == '|')
		{
			*end = 0;
	//		action(start, PIPED);
			start = end + 1;
		}
		end++;
	}
	//action(start, SEMICOLONED);
	return (0);
}
