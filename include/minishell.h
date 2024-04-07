/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:55:55 by apeposhi          #+#    #+#             */
/*   Updated: 2024/04/07 21:49:41 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lib.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define RED "\033[1;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define ORANGE "\033[38;5;202m\033[22m"
# define GRAY "\033[1;30m"
# define DEFAULT "\033[1;39m"

# define IS_INOOUT 1
# define IS_DOUBLE 2

# define FLAG_D 1
# define FLAG_S 2
# define FLAG_1 4
# define FLAG_2 8
# define FLAG_3 16

typedef struct s_data
{
	char	**envp;
	int		exit_status;
	bool	exit;
	char	*input;
}	t_data;

typedef struct s_exec
{
	char	**cmd;
	int		fd_in;
	int		fd_out;
	char	*path;
}	t_exec;

// Utils
char	*iter_quotes(char *str);
int		get_env(char **env, char *str, char **exp, t_data *data);
int		squote_handler(char **cont, int *it);
int		dquote_handler(char **cont, t_data *data, int *len, int *it);
int		dollar_handler(char **cont, t_data *data, int *len, int *it);

// Parser
int		checker(char **input);
int		iter_cmd(t_data *data);
t_list	*parse_cmd(char *str, t_data *data, t_exec *exe, bool exp_flag);

// Error
void	print_error(int flag);

// Signals
void	setup_signal_handling(void);
void	s_child_case(int sig);
void	s_heredoc_case(int sig);
void	handle_signals_extended(void (*func)(int));

// Builtins
void	b_cd(char *path, t_data *data);
void	b_echo(char **cmds);
void	b_env(char **env);
void	b_exit(t_data *data, char **args);
void	b_export(t_data *data, char *assignment);
void	b_pwd(void);
void	b_unset(char **env, char **cmds);

// Builtin utils
int		handle_error(int r_value, char *r_message);
void	handle_void_error(char *message);
void	handle_void_perror(char *message);
void	execute_builtin(t_data *data, t_exec *exe);
void	update_env_var(char ***env, const char *name, const char *value);

// Heredoc
int		handle_heredoc(const char *delimiter);

#endif
