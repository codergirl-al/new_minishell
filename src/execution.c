/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:01:36 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/20 15:32:07 by ykerdel          ###   ########.fr       */
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

static int	execute(char *cmd, t_data *data, int *stdin)
{
	t_exec	exe;
	
	dup2(*stdin, STDIN_FILENO);
	close(*stdin);

	if (!parse_cmd(cmd, data, 0, &exe))
		return (1); /// error malloc fail
	exe.path = ft_getpath(data->envp, exe.cmd[0]);
	execve(exe.path, exe.cmd, data->envp);
	return (1);
}

static int execute_pipe(char *cmd, t_data *data, int *stdin)
{
	int	fd[2];
	
	if (!pipe(fd) && !fork())
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute(cmd, data, stdin);
		return (1);
	}
	close(fd[1]);
	close(*stdin);
	*stdin = fd[0];
	return (0);
}

static int execute_last(char *cmd, t_data *data, int *stdin)
{
	if (!fork())
	{
		execute(cmd, data, stdin);
		return (1);
	}
	close(*stdin);
	while (waitpid(-1, NULL, WUNTRACED) != -1)
		;
	*stdin = dup(STDIN_FILENO);
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