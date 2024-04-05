/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:19:32 by apeposhi          #+#    #+#             */
/*   Updated: 2024/04/05 15:11:42 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	validate_export_var(const char *name)
{
	const char	*ptr;

	if (!name || !*name || !(ft_isalpha(*name)) || *name == '_')
		return (0);
	ptr = name + 1;
    if (!ft_isalpha(*ptr) && *ptr != '_')
        return (0);
	while (*ptr)
	{
		if (!ft_isalnum(*ptr) && *ptr != '_')
			return (0);
		ptr++;
	}
	return (1);
}

static void handle_reallocation(char **env, char **new_env, char *new_var)
{
	size_t	size;
	size_t	i;

	size = 0;
	while (env[size])
		++size;
	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
	{
		free(new_env);
		return (handle_void_perror("Failed to reallocate environment array"));
	}
	i = -1;
	while (++i < size)
		new_env[i] = env[i];
	env[size] = new_var;
	env[size + 1] = NULL;
}

void	handle_env(char **env, char *name)
{
	char	*new_var;
	char	**new_env;
	size_t	len;
	size_t	i;

	len = ft_strlen(name) + 2;
	new_var = malloc(len);
	new_env = NULL;
	if (!new_var)
		return (handle_void_perror("Failed to allocate memory."));
	snprintf(new_var, len, "%s", name);
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)))
		{
			free(env[i]);
			env[i] = new_var;
			return ;
		}
	}
	handle_reallocation(env, new_env, new_var);
	free(env);
	env = new_env;
    free(new_var);
    free(new_env);
}

void	b_export(t_data *data, char *assignment)
{
	char	*pos;

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
		return ;
	}
	*pos = '=';
	handle_env(data->envp, assignment);
}
