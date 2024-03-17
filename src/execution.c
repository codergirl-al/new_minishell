/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khnishou <khnishou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:01:36 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/17 03:50:43 by khnishou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_getpath(char **env, char *f_cmd)
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
	while (!access(path, X_OK))
	{
		if (s_tmp)
			free(s_tmp);
		path = tmp;
		while (*tmp && *tmp != ':')
			tmp++;
		*tmp++ = '\0';
		s_tmp = ft_strjoin(ft_strjoin(path, "/"), f_cmd);
	}
	return (s_tmp);
}

int	execute(char *commande, t_data *data, int *stdin)
{
	t_exec	*exe;
	
	dup2(*stdin, STDIN_FILENO);
	close(*stdin);
	exe->path = ft_getpath(data->envp, exe->cmd[0]);
	execve(exe->path, exe->cmd, data->envp);
	return (1);
}

int execute_pipe(char *cmd, t_data *data, int *stdin)
{
	int	fd[2];
	
	if (!pipe(fd) && fork() == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute(cmd, data, stdin);
		return (1);
	}
	else
		perror("minishell");
	close(fd[1]);
	close(*stdin);
	*stdin = fd[0];
	return (0);
}

int execute_last(char *cmd, t_data *data, int *stdin)
{
	if (!fork())
	{
		execute(cmd, data, stdin);
		return (1);
	}
	else
		perror("minishell");
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