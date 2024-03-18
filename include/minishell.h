/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:55:55 by apeposhi          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/17 21:27:09 by apeposhi         ###   ########.fr       */
=======
/*   Updated: 2024/03/18 16:42:21 by ykerdel          ###   ########.fr       */
>>>>>>> e3debbaf3369b2da6d8deceaa29e2ca6ae949060
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

// parse
int		checker(char **input);
int		iter_cmd(t_data *data);
int		parse_cmd(char *str, t_data *data, int it, t_exec *exe);

// Signals
void	setup_signal_handling(void);
void 	s_child_case(int sig);
void	s_heredoc_case(int sig);
void	handle_signals_extended(void (*func)(int));

#endif
