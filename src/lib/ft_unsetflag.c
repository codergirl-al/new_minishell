/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetflag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 18:58:18 by ykerdel           #+#    #+#             */
/*   Updated: 2024/04/07 19:00:30 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib.h"

int	ft_unsetflag(int flag, ...)
{
	va_list	args;
	int		arg;

	va_start(args, flag);
	arg = va_arg(args, int);
	while (arg != 0)
		if (flag & arg)
			flag &= ~arg;
	va_end(args);
	return (flag);
}
