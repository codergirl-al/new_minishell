/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:23:31 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/28 16:46:01 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_env_var(char **env, const char *name)
{
	size_t	name_len;
	size_t	i;

	name_len = ft_strlen(name);
	i = -1;
	while (env[++i] != NULL)
	{
		if (strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
			return (env[i] + name_len + 1);
	}
	return (NULL);
}

static void	handle_home_case(t_data *data, char *path)
{
	path = find_env_var(data->envp, path);
	if (path == NULL)
	{
		fprintf(stderr, "cd: %s not set\n", path);
		data->exit_status = 1;
		return ;
	}
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

	if (!data)
		return (handle_void_error("cd: invalid data structure\n"));
	if (getcwd(old_path, sizeof(old_path)) == NULL)
	{
		perror("cd: error getting current directory");
		data->exit_status = 1;
		return ;
	}
	if (path == NULL || *path == '\0')
		handle_home_case(data, "HOME");
	if (chdir(path) != 0)
		return (handle_cd_perror(data, "cd"));
	update_env_var(&(data->envp), "OLDPWD", old_path);
	if (getcwd(new_path, sizeof(new_path)) == NULL)
		return (handle_cd_perror(data, "cd: error getting new directory"));
	update_env_var(&(data->envp), "PWD", new_path);
	data->exit_status = 0;
}
