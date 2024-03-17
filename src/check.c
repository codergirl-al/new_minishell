/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khnishou <khnishou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:34:56 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/17 03:43:24 by khnishou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
// ...	none
// ..1	|
// .1.	&
// .11	;
// 1..		??
// 1.1	||
// 11.	&&
// 111	;;
//								+-------+
#define FLAG_D (1 << 0) //--'	|00 none|
#define FLAG_S (1 << 1) //--"	|01 "|"	|
#define FLAG_1 (1 << 2) //------*10 "&"	|
#define FLAG_2 (1 << 3) //-------11 ";"	|
#define FLAG_3 (1 << 4) //-------1 / 2	|
// 								+-------+
*/
#define FLAG_D (1 << 0)
#define FLAG_S (1 << 1)
#define FLAG_1 (1 << 2)
#define FLAG_2 (1 << 3)
#define FLAG_3 (1 << 4)
#define FLAG_4 (1 << 5)


static int	istoken(char c)
{
	return ((c == '|') || (c == '&') || (c == ';'));
}

void	print_error(int flag)
{
	char	c;

	c = 0;
	printf("minibash: syntax error near unexpected token `");
	if ((flag & FLAG_1) && !(flag & FLAG_2))
		c = '|';
	else if (!(flag & FLAG_1) && (flag & FLAG_2))
		c = '&';
	else if ((flag & FLAG_1) && (flag & FLAG_2))
		c = ';';
	printf("%c", c);
	if (flag & FLAG_3)
		printf("%c", c);
	printf("\'\n");
}

int	set_error(int flag)
{
	if (!(flag & FLAG_S))
		flag ^= FLAG_S;
	if (!(flag & FLAG_D))
		flag ^= FLAG_D;
	return (flag);
}

void	reset_flag(int *flag)
{
	if (*flag & FLAG_1)
		*flag ^= FLAG_1;
	if (*flag & FLAG_2)
		*flag ^= FLAG_2;
	if (*flag & FLAG_3)
		*flag ^= FLAG_3;
}

int	set_flag(char c, char c_next)
{
	int flag = 0;

	if (c == '|')
		flag ^= FLAG_1;
	else if (c == '&')
		flag ^= FLAG_2;
	else if (c == ';')
	{
		flag ^= FLAG_1;
	flag ^= FLAG_2;
	}
	if (c_next && c_next == c)
		flag ^= FLAG_3;
	return (flag);
}

static int	not_valid(char *str) {
	int	flag;
	int	it;
	int	len_cmd;

	flag = 0;
	it = 0;
	len_cmd = 0;
	while (str[it]) {
		if (!(flag & FLAG_S) && str[it] == '\"')
			flag ^= FLAG_D;
		else if (!(flag & FLAG_D) && str[it] == '\'')
			flag ^= FLAG_S;
		else if (!(flag & FLAG_S) && !(flag & FLAG_D) && istoken(str[it])) {
			reset_flag(&flag);
			flag ^= set_flag(str[it], str[it + 1]);
			if (!len_cmd || ((flag & FLAG_1) && (flag & FLAG_2) && (flag & FLAG_3)))
				return (set_error(flag));
			it += ((flag & FLAG_3) >> 4);
			len_cmd = 0;
		}
		if ((!isspace(str[it]) && !istoken(str[it])) || (flag & FLAG_S) ||
				(flag & FLAG_D))
			len_cmd++;
		it++;
	}
	if (len_cmd && !(flag & FLAG_S) && !(flag & FLAG_D))
		reset_flag(&flag);
	return (flag);
}

static void	interactive_promt(char **input, int flag)
{
	printf(GRAY);
	if (!(flag & FLAG_1) && (flag & FLAG_2) && (flag & FLAG_3))
		printf(" cmdand");
	else if ((flag & FLAG_1) && !(flag & FLAG_2) && (flag & FLAG_3))
		printf(" cmdor");
	else if ((flag & FLAG_1) && !(flag & FLAG_2))
		printf(" pipe");
	if (flag & FLAG_D)
		printf(" dquote");
	else if (flag & FLAG_S)
		printf(" quote");
	*input = ft_strjoin(*input, ft_strjoin("\n", readline("> " DEFAULT))); /// add '\n'
}

int	checker(char **input)
{
	int	flag;

	while (1)
	{
		flag = not_valid(*input);
		if ((flag & FLAG_S) && (flag & FLAG_D)) {
  			print_error(flag);
		return (2); // check
		}
		else if (flag)
			interactive_promt(input, flag);
		else
			return (0);
	}
}
