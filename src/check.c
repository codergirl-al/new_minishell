/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:34:56 by apeposhi          #+#    #+#             */
/*   Updated: 2024/04/01 14:36:36 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <limits.h>


#define FLAG_d (1 << 0) //--'	|00 none|
#define FLAG_s (1 << 1) //--"	|01 "|"	|
#define FLAG_1 (1 << 2) //------*10 "<"	|
#define FLAG_2 (1 << 3) //-------11 ">"	|
#define FLAG_3 (1 << 4) //-------1 / 2	|
// 								+-------+

static int istoken(char c) { return ((c == '|') || (c == '>') || (c == '<')); }

void print_error(int flag) {
  char c = 0;
  printf("minibash: syntax error near unexpected token `");
  if ((flag & FLAG_1) && !(flag & FLAG_2))
    c = '|';
  else if (!(flag & FLAG_1) && (flag & FLAG_2))
    c = '<';
  else if ((flag & FLAG_1) && (flag & FLAG_2))
    c = '>';
  printf("%c", c);
  if (flag & FLAG_3)
    printf("%c", c);
  printf("\'\n");
}

int set_error(int flag) {
  if (!(flag & FLAG_s))
    flag ^= FLAG_s;
  if (!(flag & FLAG_d))
    flag ^= FLAG_d;
  return (flag);
}

void reset_flag(int *flag) {
  if (*flag & FLAG_1)
    *flag ^= FLAG_1;
  if (*flag & FLAG_2)
    *flag ^= FLAG_2;
  if (*flag & FLAG_3)
    *flag ^= FLAG_3;
}

int set_flag(char c, char c_next) {
  int flag = 0;

  if (c == '|')
    flag ^= FLAG_1;
  else if (c == '<')
    flag ^= FLAG_2;
  else if (c == '>') {
    flag ^= FLAG_1;
    flag ^= FLAG_2;
  }
  if (c_next && c_next == c)
    flag ^= FLAG_3;
  return (flag);
}

static int not_valid(char *str) {
  int flag = 0;
  int it = 0;
  int len_cmd = 0;

  while (str[it]) {
    if (!(flag & FLAG_s) && str[it] == '\"')
      flag ^= FLAG_d;
    else if (!(flag & FLAG_d) && str[it] == '\'')
      flag ^= FLAG_s;
    else if (!(flag & FLAG_s) && !(flag & FLAG_d) && istoken(str[it])) {
      reset_flag(&flag);
      flag ^= set_flag(str[it], str[it + 1]);
      if ((!len_cmd && (flag & FLAG_1) && !(flag & FLAG_2)) || ((flag & FLAG_1) && !(flag & FLAG_2) && (flag & FLAG_3)))
        return (set_error(flag));
      it += ((flag & FLAG_3) >> 4);
      len_cmd = 0;
    }
    if ((!isspace(str[it]) && !istoken(str[it])) || (flag & FLAG_s) ||
        (flag & FLAG_d))
      len_cmd++;
    it++;
  }
  if (len_cmd && !(flag & FLAG_s) && !(flag & FLAG_d))
    reset_flag(&flag);
  return (flag);
}
// ...	none
// ..1	|
// .1.	<
// .11	>
// 1..		??
// 1.1	||
// 11.	<<
// 111	>>
//								+-------+

static void interactive_promt(char **input, int flag) {
  printf(GRAY);
  if (!(flag & FLAG_3) && !(flag & FLAG_2) && (flag & FLAG_1))
    printf(" pipe");
  else if (!(flag & FLAG_3) && (flag & FLAG_2) && !(flag & FLAG_1))
    printf(" inred");
  else if (!(flag & FLAG_3) && (flag & FLAG_2))
    printf(" outred");
  else if ((flag & FLAG_3) && (flag & FLAG_2) && (flag & FLAG_1))
    printf(" heredoc");
  if (flag & FLAG_d)
    printf(" dquote");
  else if (flag & FLAG_s)
    printf(" quote");
  *input = ft_strjoin(*input, ft_strjoin(readline("> " DEFAULT), "\n", 0), 0); // check leaks
}

int checker(char **input) {
  int flag;

  while (1) {
    flag = not_valid(*input);
    if (((flag & FLAG_s) && (flag & FLAG_d))) {
      print_error(flag);
      return (2); // check
    } else if (flag)
      interactive_promt(input, flag);
    else
      return (0);
  }
}
