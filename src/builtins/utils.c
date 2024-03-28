/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khnishou <khnishou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:00:03 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/27 16:42:37 by khnishou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	handle_error(int r_value, char *r_message)
// {
// 	perror(r_message);
// 	return (r_value);
// }

// void	handle_void_perror(char *message)
// {
// 	perror(message);
// 	return ;
// }

// void	handle_void_error(char *message)
// {
// 	fprintf(stderr, message);
// 	return ;
// }

// void	execute_builtin(t_data *data, t_exec *exe)
// {
// 	if (!strcmp("cd", exe->cmd[0]))
// 		b_cd(exe->cmd[1], data);
// 	else if (!strcmp("echo", exe->cmd[0]))
// 		b_echo(exe->cmd);
// 	else if (!strcmp("env", exe->cmd[0]))
// 		b_env(data->envp);
// 	else if (!strcmp("exit", exe->cmd[0]))
// 		b_exit(data);
// 	else if (!strcmp("export", exe->cmd[0]))
// 		b_export(data->envp, exe->cmd[1]);
// 	else if (!strcmp("pwd", exe->cmd[0]))
// 		b_pwd();
// 	else if (!strcmp("unset", exe->cmd[0]))
// 		b_unset(data->envp, exe->cmd);
// }

// void	update_env_var(char ***env, const char *name, const char *value)
// {
// 	size_t	i;
// 	size_t	len;
// 	char	*new_var;

// 	i = -1;
// 	while ((*env)[++i] != NULL)
// 	{
// 		if (strncmp((*env)[i], name, strlen(name)) == 0 && 
// 			(*env)[i][strlen(name)] == '=')
// 		{
// 			free((*env)[i]);
// 			len = strlen(name) + strlen(value) + 2;
// 			new_var = malloc(len);
// 			if (new_var == NULL)
// 				return (handle_void_perror("Failed to allocate memory."));
// 			snprintf(new_var, len, "%s=%s", name, value);
// 			(*env)[i] = new_var;
// 			return ;
// 		}
// 	}
// }
