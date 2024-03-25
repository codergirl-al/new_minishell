/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:23:45 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/25 18:18:17 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	b_unset(t_data data, char **cmds)
{
	size_t	i;
	size_t	j;
	size_t	k;
	int	key_len;
	
	if (!data.envp || !cmds)
		return (handle_void_error("Invalid arguments provided.\n"));
	k = 0;
	while (cmds[++k])
	{
		i = 0;
		key_len = ft_strlen(cmds[k]);
		while ((data.envp)[i] != NULL)
		{
			if (strncmp((data.envp)[i], cmds[k], key_len) == 0 && (data.envp)[i][key_len] == '=')
			{
				free((data.envp)[i]);
				j = i;
				while ((data.envp)[j] != NULL)
				{
					(data.envp)[j] = (data.envp)[j + 1];
					j++;
				}
				break;
			}
			i++;
		}
	}
}
