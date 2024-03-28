/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:00:03 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/28 15:17:18 by ykerdel          ###   ########.fr       */
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
// 	fprintf(stderr, "%s", message);
// 	return ;
// }

// void	execute_builtin(t_data *data, t_exec *exe)
// {
// 	if (!strcmp("cd", exe->cmd[0]))
// 		b_cd(exe->cmd[1], data);
// 	else if (!ft_strncmp("echo", exe->cmd[0], 5))
// 		b_echo(exe->cmd);
// 	else if (!ft_strncmp("env", exe->cmd[0], 4))
// 		b_env(data->envp);
// 	else if (!ft_strncmp("exit", exe->cmd[0], 5))
// 		b_exit(data, exe->cmd);
// 	else if (!ft_strncmp("export", exe->cmd[0], 7))
// 		b_export(data, exe->cmd[1]);
// 	else if (!ft_strncmp("pwd", exe->cmd[0], 4))
// 		b_pwd();
// 	else if (!ft_strncmp("unset", exe->cmd[0], 6))
// 		b_unset(data->envp, exe->cmd);
// }

// void	update_env_var(char ***env, const char *name, const char *value)
// {
// 	size_t	i;
//  	size_t	len;
//  	char	*new_var;

// 	i = -1;
// 	while ((*env)[++i] != NULL)
// 	{
// 		if (ft_strncmp((*env)[i], name, strlen(name)) == 0 && \
// 			(*env)[i][strlen(name)] == '=')
// 		{
// 			free((*env)[i]);
// 			len = ft_strlen(name) + strlen(value) + 2;
// 			new_var = malloc(len);
// 			if (new_var == NULL)
// 				return (handle_void_perror("Failed to allocate memory."));
// 			snprintf(new_var, len, "%s=%s", name, value);
// 			(*env)[i] = new_var;
// 			return ;
// 		}
// 	}
// }
