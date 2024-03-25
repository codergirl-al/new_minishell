/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:19:32 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/21 16:22:09 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	validate_export_var(const char *name)
{
	const char	*ptr;

	if (!name || !*name || !(ft_isalpha(*name)) || *name == '_')
		return (0);
	ptr = name;
	while (*ptr)
	{
		if (!ft_isalnum(*ptr) && *ptr != '_')
			return (0);
		ptr = name + 1;
	}
	return (1);
}

static void	handle_reallocation(char **env, char **new_env, char *new_var)
{
	size_t	size;
	size_t	i;

	size = 0;
	while (env[size])
		++size;
	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
	{
		free(new_var);
		return (handle_void_perror("Failed to reallocate environment array"));
	}
	i = -1;
	while (++i < size)
		new_env[i] = env[i];
	env[size] = new_var;
	env[size + 1] = NULL;
}

void	handle_env(char **env, const char *name, const char *value)
{
	char	*new_var;
	char	**new_env;
	size_t	len;
	size_t	i;

	len = ft_strlen(name) + ft_strlen(value) + 2;
	new_var = malloc(len);
	if (!new_var)
		return (handle_void_perror("Failed to allocate memory for new environment variable"));
	snprintf(new_var, len, "%s=%s", name, value);
	i = -1;
	while ((*env)[++i])
	{
		if (ft_strncmp(env[i], name, strlen(name)) == 0 && env[i][strlen(name)] == '=')
		{
			free(env[i]);
			env[i] = new_var;
			return ;
		}
	}
	handle_reallocation(env, new_env, new_var);
	free(env);
	env = new_env;
}

void	b_export(char **env, char *assignment)
{
	char	*pos;
	char	*name;
	char	*value;

	if (!assignment)
		return (handle_void_error("export: Missing argument\n"));
	pos = ft_strchr(assignment, '=');
	if (!pos || pos == assignment)
		return (handle_void_error("export: Invalid assignment\n"));
	*pos = '\0';
	if (!validate_export_var(assignment))
	{
		fprintf(stderr, "export: '%s' is not a valid identifier\n", assignment);
		*pos = '=';
		return;
	}
	*pos = '=';
	name = assignment;
	value = pos + 1;
	handle_env(env, name, value);
}
