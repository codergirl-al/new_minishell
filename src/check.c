/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:34:56 by apeposhi          #+#    #+#             */
/*   Updated: 2024/04/07 16:53:00 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	set_flag(char c, char c_next)
{
	int	flag;

	flag = 0;
	if (c == '|')
		flag ^= FLAG_1;
	else if (c == '<')
		flag ^= FLAG_2;
	else if (c == '>')
	{
		flag ^= FLAG_1;
		flag ^= FLAG_2;
	}
	if (c_next && c_next == c)
		flag ^= FLAG_3;
	return (flag);
}

static int	check_char(int *flag, int *len_cmd, int *it, char *str)
{
	if ((!(*len_cmd) && ((*flag) & FLAG_2)))
	{
		(*flag) = ft_setflag((*flag), FLAG_s, FLAG_d);
		return (1);
	}
	(*flag) = set_flag(str[(*it)], str[(*it) + 1]);
	if ((!(*len_cmd) && ((*flag) & FLAG_1) && !((*flag) & FLAG_2))
		|| (((*flag) & FLAG_1) && !((*flag) & FLAG_2) && ((*flag) & FLAG_3)))
	{
		(*flag) = ft_setflag((*flag), FLAG_s, FLAG_d);
		return (1);
	}
	(*it) += (((*flag) & FLAG_3) >> 4);
	(*len_cmd) = 0;
	return (0);
}

static int	not_valid(char *str)
{
	int	flag;
	int	it;
	int	len_cmd;

	flag = 0;
	it = 0;
	len_cmd = 0;
	while (str[it])
	{
		if (!(flag & FLAG_s) && str[it] == '\"')
			flag ^= FLAG_d;
		else if (!(flag & FLAG_d) && str[it] == '\'')
			flag ^= FLAG_s;
		else if (!(flag & FLAG_s) && !(flag & FLAG_d) && istoken(str[it]))
			if (check_char(&flag, &len_cmd, &it, str))
				return (flag);
		if ((!ft_issep(str[it]) && !istoken(str[it])) || (flag & FLAG_s)
			|| (flag & FLAG_d))
			len_cmd++;
		it++;
	}
	if (len_cmd && !(flag & FLAG_s) && !(flag & FLAG_d))
		flag = ft_unsetflag(flag, FLAG_1, FLAG_2, FLAG_3);
	return (flag);
}

static void	interactive_promt(char **input, int flag)
{
	printf(GRAY);
	if (!(flag & FLAG_3) && !(flag & FLAG_2) && (flag & FLAG_1))
		printf(" pipe");
	else if (!(flag & FLAG_3) && (flag & FLAG_2) && !(flag & FLAG_1))
		printf(" inred");
	else if ((flag & FLAG_2) && (flag & FLAG_1))
		printf(" outred");
	else if ((flag & FLAG_3) && (flag & FLAG_2) && !(flag & FLAG_1))
		printf(" heredoc");
	if (flag & FLAG_d)
		printf(" dquote");
	else if (flag & FLAG_s)
		printf(" quote");
	*input = ft_strjoin(*input, ft_strjoin("\n", readline("> " DEFAULT),
				STRFREE_S2), STRFREE_S1 | STRFREE_S2);
}

int	checker(char **input)
{
	int	flag;

	while (1)
	{
		flag = not_valid(*input);
		if (((flag & FLAG_s) && (flag & FLAG_d)))
		{
			print_error(flag);
			return (2);
		}
		else if (flag)
			interactive_promt(input, flag);
		else
			return (0);
	}
}
