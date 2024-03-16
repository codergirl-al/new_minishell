/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 20:47:49 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/15 17:13:51 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	action(char *cmd, int type, t_list *commands)
{
	t_command	current;

	current.cmd = cmd;
	current.type = type;
	commands = ft_lstnew(&current);
	commands->next = NULL;
	return (0);
}

int parse_cmd(t_exec *exe, char *str)
{
	t_list *tmp;
	t_list *lst;
	char *start;
	char *end;

	start = str;
	end = str;
	tmp = lst;
	while (str && *end != '\0')
	{
		if (is_sep(*end))
		{
			*end = 0;
			action(start, PIPED, tmp);
			start = end + 1;
			tmp = tmp->next;
		}
		end++;
	}
	action(start, SEMICOLONED, tmp);
	return (0);	
	return (0);
}

int	ft_parse_input(char *input, t_list	*cmds)
{
	t_list	*tmp;
	char	*start;
	char	*end;

	start = input;
	end = input;
	tmp = cmds;
	while (input && *end != '\0')
	{
		if (*end == '|')
		{
			*end = 0;
			action(start, PIPED, tmp);
			start = end + 1;
			tmp = tmp->next;
		}
		end++;
	}
	action(start, SEMICOLONED, tmp);
	return (0);
}
