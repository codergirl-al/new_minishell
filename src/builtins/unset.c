/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:23:45 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/27 13:57:47 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	b_unset(char **env, char **cmds)
{
	size_t	i;
	size_t	j;
	size_t	k;
	int		key_len;

	if (!env || !cmds)
		return (handle_void_error("Invalid arguments provided.\n"));
	k = 0;
	while (cmds[++k])
	{
		i = -1;
		key_len = ft_strlen(cmds[k]);
		while (env[i] != NULL)
		{
			if (strncmp(env[++i], cmds[k], key_len) == 0 && \
				env[i][key_len] == '=')
			{
				free(env[i]);
				j = i - 1;
				while (env[++j] != NULL)
					env[j] = env[j + 1];
				break ;
			}
		}
	}
}
