/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:19:32 by apeposhi          #+#    #+#             */
/*   Updated: 2024/04/08 15:26:14 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	h_realloc(char ***env, char ***new_env, char **new_var, const char *nm)
{
	size_t	i;
	size_t	new_size;

	i = -1;
	while ((*env)[++i])
	{
		if (ft_strncmp((*env)[i], nm, ft_strlen(nm)) == 0
				&& (*env)[i][ft_strlen(nm)] == '=')
		{
			free((*env)[i]);
			(*env)[i] = (*new_var);
			return ;
		}
	}
	new_size = sizeof(char *) * (i + 2);
	(*new_env) = malloc(new_size);
	if (!(*new_env))
	{
		perror("Failed to reallocate environment array.");
		free(new_var);
		exit(EXIT_FAILURE);
	}
	ft_copy_over(new_env, env, new_var, i);
}

void	handle_env(char ***env, const char *name, const char *value)
{
	char	*new_var;
	char	**new_env;

	new_env = NULL;
	new_var = malloc(ft_strlen(name + ft_strlen(value) + 2));
	if (!new_var)
	{
		perror("Failed to allocate memory.");
		exit(EXIT_FAILURE);
	}
	build_string(new_var, name, value);
	h_realloc(env, &new_env, &new_var, name);
	free(*env);
	*env = new_env;
}

static void	ft_export_print(t_data *data)
{
	int	i;

	i = -1;
	while (data->envp[++i])
		printf("declare -x %s\n", data->envp[i]);
}

int	b_export(t_data *data, char *assignment)
{
	const char	*name;
	const char	*value;
	char		*pos;

	if (!assignment)
	{
		ft_export_print(data);
		return (0);
	}
	name = assignment;
	value = NULL;
	pos = ft_strchr(assignment, '=');
	if (pos)
	{
		*pos = '\0';
		value = pos + 1;
	}
	if (!validate_export_var(name))
	{
		printf("export: '%s' is not a valid identifier\n", name);
		if (pos)
			*pos = '=';
		return (1);
	}
	handle_env(&(data->envp), name, value);
	return (0);
}
