/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:23:31 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/19 17:33:13 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int update_cwd(void)
{
	char	*cwd;
    int		result;

    cwd = getcwd(NULL, 0);
    if (!cwd)
		return (handle_error(1, "minishell: error retrieving current directory"));
	result = update_env("PWD", cwd, 0);
	free(cwd);
	return (result == 0 ? 0 : 1);
}

static int	goto_home(char **env)
{
	char	*home;
	
	home = ft_arrcmp((void **)env, "HOME=");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		return (1);
	}
	if (chdir(home) != 0)
		return (handle_error(1, "minishell: cd: error changing to HOME directory"));
	return (update_cwd());
}

static int cd_error_message(char *path) {
	ft_putstr_fd("minishell: cd: `", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd("': No such file or directory\n", STDERR_FILENO);
	return (1);
}

int b_cd(char *path, char **env)
{
	if (!path)
		return (goto_home(env));
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
