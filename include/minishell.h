/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:55:55 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/16 15:27:41 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lib.h"
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "lib.h"
# define RED "\033[1;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define ORANGE "\033[38;5;202m\033[22m"
# define GRAY "\033[1;30m"
# define DEFAULT "\033[1;39m"

int	g_sig;

enum e_type
{
	PIPED = 1,
	SEMICOLONED = 0,
};

typedef struct s_data
{
	char	**envp;
	int		exit_status;
	bool	exit;
	char	*input;
	char	*prev_input;
}	t_data;

typedef struct s_exec
{
	char	**cmd;
	int		fd_in;
	int		fd_out;
	char	*path;
}	t_exec;

typedef struct s_command
{
	char	*cmd;
	int		type;
}	t_command;

int		checker(char **input);
int		ft_parse_input(char *input, t_list	*lst);
int		parse_cmd(t_exec *exe, char *str);
void	setup_signal_handling(void);

#endif
