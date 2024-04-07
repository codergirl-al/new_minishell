/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:23:45 by apeposhi          #+#    #+#             */
/*   Updated: 2024/04/08 00:05:09 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	b_unset(char **env, char **cmds)
{
	size_t	i;
	size_t	j;
	size_t	k;
	int		key_len;

	if (!cmds[1])
		return (0);
	k = 0;
	while (cmds[++k])
	{
		if (!validate_export_var(cmds[k]))
			return (1);
		i = -1;
		key_len = ft_strlen(cmds[k]);
		while (env[++i] != NULL)
		{
			if (!ft_strncmp(env[i], cmds[k], key_len) && env[i][key_len] == '=')
			{
				free(env[i]);
				j = i - 1;
				while (env[++j])
					env[j] = env[j + 1];
				break ;
			}
		}
	}
	return (0);
}
