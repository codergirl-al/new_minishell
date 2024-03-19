/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:00:03 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/19 16:21:49 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	update_env(char *name, char *old, int tof)
{
	return (0);
}

int	handle_error(int r_value, char *r_message)
{
	perror(r_message);
	return (r_value);
}

// char	*get_env_value(char **env, char *val)
// {
// 	char	*wanted_value;
	
// 	wanted_value = ft_arrcmp((void **)env, val);
// 	return (wanted_value);
// }
