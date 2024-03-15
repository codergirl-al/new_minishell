/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:01:36 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/15 13:05:28 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_getpath(char **env, char *f_cmd)
{
	char	*path;
	char	*tmp;
	char	*s_tmp;

	s_tmp = NULL;
	path = ft_arrcmp(env, "PATH=");
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

int	execute(t_command *commande, t_data *data)
{
	char	*path;
	char	**arr;

	parse_cmd(&arr, commande->cmd);
	path = ft_getpath(data->envp, arr[0]);
	dup2(stdin, STDIN_FILENO);
	close(stdin);
	execve(path, arr, data->envp);
	return (1);
}

int	execution(t_list *list, t_data *data)
{
	int			stdin;
	int			fd[2];
	t_list		*tmp;
	t_command	*cmd;

	tmp = list;
	stdin = dup(STDIN_FILENO);
	while (tmp)
	{
		cmd = (t_command *) list->content;
		if (cmd->type == SEMICOLONED)
		{
			if (!fork())
			{
				execute(cmd, data);
				return (1);
			}
			close(stdin);
			while (waitpid(-1, NULL, WUNTRACED) != -1)
				;
			stdin = dup(STDIN_FILENO);
		}
		else if (cmd->type == PIPED)
		{
			pipe(fd);
			if (fork() == 0)
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				execute(cmd, data);
				return (1);
			}
			close(fd[1]);
			close(stdin);
			stdin = fd[0];
		}
		tmp = tmp->next;
	}
	close(stdin);
	return (0);
}
