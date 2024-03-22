/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khnishou <khnishou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:55:55 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/22 00:40:50 by khnishou         ###   ########.fr       */
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

// int	g_sig;

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

// utils
char	*iter_quotes(char *str);
char	*get_env(char **env, char *var_name);
int		cmdlen(char *str);

// parse
int		checker(char **input);
int		iter_cmd(t_data *data);
int		parse_cmd(char *str, t_data *data, int it, t_exec *exe);

// Signals
void	setup_signal_handling(void);
void 	s_child_case(int sig);
void	s_heredoc_case(int sig);
void	handle_signals_extended(void (*func)(int));

// Builtins
void	b_cd(t_data *data, char **args);
void	echo(char **args);
void	b_env(t_data *data);
void	b_exit(t_data *data, char **args);
void	b_export(t_data *data, char **args);
void	b_pwd(void);
void	b_unset(t_data *data, char **args);

#endif
