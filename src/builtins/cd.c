/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:23:31 by apeposhi          #+#    #+#             */
/*   Updated: 2024/04/08 15:25:49 by apeposhi         ###   ########.fr       */
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

int	handle_home_case(t_data *data, const char *var_name)
{
	char	*home_path;

	home_path = get_env_var_value(data->envp, var_name);
	if (home_path == NULL)
	{
		printf("cd: %s not set\n", var_name);
		return (1);
	}
	if (chdir(home_path) != 0)
		return (handle_error(1, "cd: error changing to home directory"));
	return (0);
}

int	b_cd(char *path, t_data *data)
{
	char	old_path[1024];
	char	new_path[1024];

	if (!data)
		return (handle_error(1, "cd: invalid data structure"));
	if (getcwd(old_path, sizeof(old_path)) == NULL)
	{
		perror("cd: error getting current directory");
		return (1);
	}
	if (!path || !ft_strncmp(path, "~", 2) || path == NULL)
		handle_home_case(data, "HOME");
	else if (chdir(path) != 0)
		return (handle_error(1, "cd"));
	if (data->exit_status == 0)
	{
		update_env_var(&(data->envp), "OLDPWD", old_path);
		if (getcwd(new_path, sizeof(new_path)) == NULL)
			return (handle_error(1, "cd: error getting new directory"));
	}
	update_env_var(&(data->envp), "PWD", new_path);
	return (0);
}
