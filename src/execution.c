/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:01:36 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/28 15:01:25 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_getpath(char **env, char *f_cmd)
{
	char	*path;
	char	*tmp;
	char	*s_tmp;

	s_tmp = NULL;
	path = ft_arrcmp((void **)env, "PATH=");
	if (!path)
		return (NULL);
	path += 5;
	tmp = path;
	while (access(s_tmp, X_OK))
	{
		if (s_tmp)
			free(s_tmp);
		path = tmp;
		while (*tmp && *tmp != ':')
			tmp++;
		*tmp++ = '\0';
		s_tmp = ft_strjoin(path, ft_strjoin("/", f_cmd, 0), STRFREE_S2);
	}
	return (s_tmp);
}

static int	execute(t_list *lst, t_data *data, int *stdin, t_exec exe)
{
	exe.cmd = lst_to_arr(lst);
	dup2(*stdin, STDIN_FILENO);
	close(*stdin);
	exe.path = ft_getpath(data->envp, exe.cmd[0]);
	if (exe.fd_in > 0)
	{
		dup2(exe.fd_in, STDIN_FILENO);
		close(exe.fd_in);	
	}
	if (exe.fd_out > 0)
	{
		dup2(exe.fd_out, STDOUT_FILENO);
		close(exe.fd_out);	
	}
	execve(exe.path, exe.cmd, data->envp);
	return (1);
}

static int execute_pipe(char *cmd, t_data *data, int *stdin)
{
	int	fd[2];
	t_exec	exe;
	t_list	*lst;

	exe.fd_in = 0;
	exe.fd_out = 0;
	lst = parse_cmd(cmd, data, &exe, true);
	if (!pipe(fd) && !fork())
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute(lst, data, stdin, exe);
		return (1);
	}
	close(fd[1]);
	close(*stdin);
	*stdin = fd[0];
// free_lst
	return (0);
}

static int	is_builtin(t_list *lst) {
	if (!strcmp("cd", (char *)lst->content))
		return (1);
	else if (!ft_strncmp("echo", (char *)lst->content, 5))
		return (1);
	else if (!ft_strncmp("env", (char *)lst->content, 4))
		return (1);
	else if (!ft_strncmp("exit", (char *)lst->content, 5))
		return 1;
	else if (!ft_strncmp("export", (char *)lst->content, 7))
		return (1);
	else if (!ft_strncmp("pwd", (char *)lst->content, 4))
		return (1);
	else if (!ft_strncmp("unset", (char *)lst->content, 6))
		return (1);
	return (0);
}

static int execute_last(char *cmd, t_data *data, int *stdin)
{
	t_exec	exe;
	t_list	*lst;

	exe.fd_in = 0;
	exe.fd_out = 0;
	lst = parse_cmd(cmd, data, &exe, true);
	if (is_builtin(lst)) {
		exe.cmd = lst_to_arr(lst);
		execute_builtin(data, &exe);
	}
	else if (!fork())
	{
		execute(lst, data, stdin, exe);
		return (1);
	}
	close(*stdin);
	while (waitpid(-1, NULL, WUNTRACED) != -1)
		;
	*stdin = dup(STDIN_FILENO);
// free_lst
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
		if (*end == '|')
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
