/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:01:36 by apeposhi          #+#    #+#             */
/*   Updated: 2024/04/08 17:02:24 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_getpath(char **env, char *f_cmd)
{
	int		it;
	char	*path;
	char	*tmp;
	char	*s_tmp;

	it = 1;
	s_tmp = NULL;
	tmp = ft_arrcmp((void **)env, "PATH=");
	if (!tmp)
		return (NULL);
	path = ft_strdup(tmp + 5);
	tmp = path;
	while (*path && (it || access(s_tmp, X_OK)))
	{
		it = 0;
		if (s_tmp)
			free(s_tmp);
		path = tmp;
		while (*tmp && *tmp != ':')
			tmp++;
		if (*tmp && *tmp == ':')
			*tmp++ = '\0';
		s_tmp = ft_strjoin(path, ft_strjoin("/", f_cmd, 0), STRFREE_S2);
	}
	return (s_tmp);
}

static int	execute(t_list *lst, t_data *data, int *stdin, t_exec exe)
{	
	exe.cmd = lst_to_arr(lst);
	if (!exe.cmd)
		return (0);
	dup2(*stdin, STDIN_FILENO);
	close(*stdin);
	if (exe.fd_in > 2)
	{
		dup2(exe.fd_in, STDIN_FILENO);
		close(exe.fd_in);
	}
	if (exe.fd_out > 2)
	{
		dup2(exe.fd_out, STDOUT_FILENO);
		close(exe.fd_out);
	}
	exe.path = ft_getpath(data->envp, exe.cmd[0]);
	if (!exe.path)
	{
		write(2, "minishell: command not found\n", 30);
		return (127);
	}
	execve(exe.path, exe.cmd, data->envp);
	write(2, "minishell: command not found\n", 30);
	return (127);
}

static int	execute_pipe(char *cmd, t_data *data, int *stdin)
{
	int		fd[2];
	t_exec	exe;
	t_list	*lst;

	exe.fd_in = 0;
	exe.fd_out = 1;
	lst = parse_cmd(cmd, data, &exe, true);
	if (exe.fd_in < 0 || exe.fd_out < 0)
		return (0);
	if (!pipe(fd) && !fork())
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (ft_isbuiltin(lst))
		{
			exe.cmd = lst_to_arr(lst);
			execute_builtin(lst, data, &exe, 1);
		}
		else
			execute(lst, data, stdin, exe);
	}
	close(fd[1]);
	close(*stdin);
	*stdin = fd[0];
	ft_lstfree(lst);
	return (0);
}

static int	execute_last(char *cmd, t_data *data, int *stdin)
{
	t_exec	exe;
	t_list	*lst;
	int		tmp;

	exe.fd_in = 0;
	exe.fd_out = 1;
	lst = parse_cmd(cmd, data, &exe, true);
	if (exe.fd_in < 0 || exe.fd_out < 0)
		return (0);
	if (lst && ft_isbuiltin(lst))
		tmp = execute_builtin(lst, data, &exe, 0);
	else if (lst)
	{
		if (!fork())
			exit(execute(lst, data, stdin, exe));
		close(*stdin);
		while (waitpid(-1, &tmp, WUNTRACED) != -1)
			;
		data->exit_status = (tmp >> 8) & 0x000000ff;
	}
	*stdin = dup(STDIN_FILENO);
	ft_lstfree(lst);
	return (0);
}

int	iter_cmd(t_data *data)
{
	char	*start;
	char	*end;
	int		stdin;

	start = data->input;
	end = data->input;
	stdin = dup(STDIN_FILENO);
	while (data->input && *end)
	{
		if (*end == '\'' || *end == '\"')
			end = iter_quotes(end);
		else if (*end == '|')
		{
			*end = 0;
			execute_pipe(start, data, &stdin);
			start = end + 1;
		}
		end++;
	}
	execute_last(start, data, &stdin);
	close(stdin);
	return (0);
}
