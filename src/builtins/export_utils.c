/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:13:26 by apeposhi          #+#    #+#             */
/*   Updated: 2024/04/07 20:13:27 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	validate_export_var(const char *name)
{
	const char	*ptr;

	if (!name || !*name || ((!ft_isalpha(*name)) && *name != '_'))
		return (0);
	ptr = name + 1;
	if (!ft_isalnum(*ptr) && *ptr != '_')
		return (0);
	while (*ptr && *ptr != '=')
	{
		if (!ft_isalnum(*ptr) && *ptr != '_')
			return (0);
		ptr++;
	}
	return (1);
}

void	build_string(char *new_var, const char *name, const char *value)
{
	if (!new_var || !name)
	{
		printf("Invalid argument(s)\n");
		return ;
	}
	strcpy(new_var, name);
	if (value)
	{
		strcat(new_var, "=");
		strcat(new_var, value);
	}
}

void	ft_copy_over(char ***new_env, char ***env, char **new_var, size_t i)
{
	size_t	j;

	j = -1;
	while (++j < i)
		(*new_env)[j] = (*env)[j];
	(*new_env)[i] = (*new_var);
	(*new_env)[i + 1] = NULL;
}
