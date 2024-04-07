/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetflag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 18:58:18 by ykerdel           #+#    #+#             */
/*   Updated: 2024/04/07 20:05:00 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib.h"

int	ft_unsetflag(int flag, ...)
{
	va_list	args;
	int		arg;

	va_start(args, flag);
	arg = va_arg(args, int);
	while (arg)
	{
		if (flag & arg)
			flag &= ~arg;
		arg = va_arg(args, int);
	}
	va_end(args);
	return (flag);
}
