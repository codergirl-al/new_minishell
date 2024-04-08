/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:55:55 by apeposhi          #+#    #+#             */
/*   Updated: 2024/04/08 17:01:09 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lib.h"
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

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
int		b_cd(char *path, t_data *data);
int		b_echo(char **cmds);
int		b_env(char **env);
int		b_exit(char **args);
int		b_export(t_data *data, char *assignment);
int		b_pwd(void);
int		b_unset(char **env, char **cmds);

// Builtin utils
int		handle_error(int r_value, char *r_message);
int		execute_builtin(t_list *lst, t_data *data, t_exec *exe, int exit_flag);
int		update_env_var(char ***env, const char *name, const char *value);
void	build_string(char *new_var, const char *name, const char *value);
int		validate_export_var(const char *name);

// Heredoc
int		handle_heredoc(const char *delimiter, t_data *data);
void	build_string(char *new_var, const char *name, const char *value);
void	ft_copy_over(char ***new_env, char ***env, char **new_var, size_t i);

#endif
