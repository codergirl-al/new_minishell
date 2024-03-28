/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:55:55 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/28 14:40:48 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lib.h"
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
# include "lib.h"
# include <limits.h>

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

typedef struct s_arg
{
	char	*arg;
}	t_arg;

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

// Utils
char	*iter_quotes(char *str);
int		get_env(char **env, char *str, char **exp);

// Parser
int		checker(char **input);
int		iter_cmd(t_data *data);
t_list	*parse_cmd(char *str, t_data *data, t_exec *exe, bool exp_flag);

// Signals
void	setup_signal_handling(void);
void	s_child_case(int sig);
void	s_heredoc_case(int sig);
void	handle_signals_extended(void (*func)(int));

// Builtins
void	b_cd(char *path, t_data *data);
void	b_echo(char **cmds);
void	b_env(char	**env);
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

#endif
