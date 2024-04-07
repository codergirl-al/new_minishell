/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:23:31 by apeposhi          #+#    #+#             */
/*   Updated: 2024/04/07 22:19:52 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env_var_value(char **envp, const char *name)
{
	size_t	name_len;
	int		i;

	if (!envp || !name)
		return (NULL);
	name_len = ft_strlen(name);
	i = -1;
	while (envp[++i] != NULL)
	{
		if (strncmp(envp[i], name, name_len) == 0 && envp[i][name_len] == '=')
			return (envp[i] + name_len + 1);
	}
	return (NULL);
}

void	handle_home_case(t_data *data, const char *var_name)
{
	char	*home_path;

	home_path = get_env_var_value(data->envp, var_name);
	if (home_path == NULL)
	{
		fprintf(stderr, "cd: %s not set\n", var_name);
		data->exit_status = 1;
		return ;
	}
	if (chdir(home_path) != 0)
	{
		perror("cd: error changing to home directory");
		data->exit_status = 1;
	}
	else
		data->exit_status = 0;
}

static void	handle_cd_perror(t_data *data, char *message)
{
	perror(message);
	data->exit_status = 1;
	return ;
}

void	b_cd(char *path, t_data *data)
{
	char	old_path[1024];
	char	new_path[1024];

	data->exit = 0;
	if (!data)
		return (handle_void_error("cd: invalid data structure\n"));
	if (getcwd(old_path, sizeof(old_path)) == NULL)
	{
		perror("cd: error getting current directory");
		data->exit_status = 1;
		return ;
	}
	if (!path || !ft_strncmp(path, "~", 2) || path == NULL)
		handle_home_case(data, "HOME");
	else if (chdir(path) != 0)
		return (handle_cd_perror(data, "cididi"));
	if (data->exit_status == 0)
	{
		update_env_var(&(data->envp), "OLDPWD", old_path);
		if (getcwd(new_path, sizeof(new_path)) == NULL)
			return (handle_cd_perror(data, "cd: error getting new directory"));
	}
	update_env_var(&(data->envp), "PWD", new_path);
	data->exit_status = 0;
}
