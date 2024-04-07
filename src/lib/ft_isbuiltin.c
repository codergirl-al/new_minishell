/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbuiltin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 22:37:52 by apeposhi          #+#    #+#             */
/*   Updated: 2024/04/07 22:39:43 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib.h"

int	ft_isbuiltin(t_list *lst)
{
	if (!ft_strncmp("cd", (char *)lst->content, 3))
		return (1);
	else if (!ft_strncmp("echo", (char *)lst->content, 5))
		return (1);
	else if (!ft_strncmp("env", (char *)lst->content, 4))
		return (1);
	else if (!ft_strncmp("exit", (char *)lst->content, 5))
		return (1);
	else if (!ft_strncmp("export", (char *)lst->content, 7))
		return (1);
	else if (!ft_strncmp("pwd", (char *)lst->content, 4))
		return (1);
	else if (!ft_strncmp("unset", (char *)lst->content, 6))
		return (1);
	return (0);
}
