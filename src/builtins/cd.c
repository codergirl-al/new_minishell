/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:23:31 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/19 11:23:10 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int update_cwd(void)
{
	char	*cwd;
    int		result;

    cwd = getcwd(NULL, 0);
    if (!cwd)
	{
		perror("minishell: error retrieving current directory");
		return (1);
	}
	result = update_env("PWD", cwd, 0);
	free(cwd);
	return (result == 0 ? 0 : 1);
}

static int	cd_to_home(void)
{
	char	*home;
	
	home = get_env_value("HOME");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		return (1);
	}
	if (chdir(home) != 0)
	{
		perror("minishell: cd: error changing to HOME directory");
		return (1);
	}
	return (update_cwd());
}

static int cd_error_message(const char *path) {
	ft_putstr_fd("minishell: cd: `", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd("': No such file or directory\n", STDERR_FILENO);
	return (1);
}

int b_cd(char *path)
{
	if (!path)
		return (cd_to_home());

	char *oldpwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		free(oldpwd);
		return (cd_error_message(path));
	}

	update_env("OLDPWD", oldpwd, 0);
	free(oldpwd);

	return (update_cwd());
}
