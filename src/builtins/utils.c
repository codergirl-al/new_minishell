/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:00:03 by apeposhi          #+#    #+#             */
/*   Updated: 2024/04/08 00:12:47 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_error(int r_value, char *r_message)
{
	perror(r_message);
	return (r_value);
}

int	execute_builtin(t_data *data, t_exec *exe, int exit_flag)
{
	int exit_n;

	if (!ft_strncmp("cd", exe->cmd[0], 3))
		exit_n = b_cd(exe->cmd[1], data);
	else if (!ft_strncmp("echo", exe->cmd[0], 5))
		exit_n = b_echo(exe->cmd);
	else if (!ft_strncmp("env", exe->cmd[0], 4))
		exit_n = b_env(data->envp);
	else if (!ft_strncmp("exit", exe->cmd[0], 5))
		exit_n = b_exit(exe->cmd);
	else if (!ft_strncmp("export", exe->cmd[0], 7))
		exit_n = b_export(data, exe->cmd[1]);
	else if (!ft_strncmp("pwd", exe->cmd[0], 4))
		exit_n = b_pwd();
	else if (!ft_strncmp("unset", exe->cmd[0], 6))
		exit_n = b_unset(data->envp, exe->cmd);
	if (exit_flag)
		exit(exit_n);
	return (exit_n);
}

int	update_env_var(char ***env, const char *name, const char *value)
{
	size_t	i;
	size_t	len;
	char	*new_var;

	i = -1;
	while ((*env)[++i] != NULL)
	{
		if (ft_strncmp((*env)[i], name, ft_strlen(name)) == 0 && \
			(*env)[i][ft_strlen(name)] == '=')
		{
			free((*env)[i]);
			len = ft_strlen(name) + ft_strlen(value) + 2;
			new_var = malloc(len);
			if (new_var == NULL)
				return (handle_error(1, "Failed to allocate memory."));
			snprintf(new_var, len, "%s=%s", name, value);
			(*env)[i] = new_var;
			return (1);
		}
	}
	return (0);
}
