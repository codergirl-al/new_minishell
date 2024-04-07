/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setflag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 19:09:31 by ykerdel           #+#    #+#             */
/*   Updated: 2024/04/07 20:04:17 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib.h"

int	ft_setflag(int flag, ...)
{
	va_list	args;
	int		arg;

	va_start(args, flag);
	arg = va_arg(args, int);
	while (arg)
	{
		if (!(flag & arg))
			flag |= arg;
		arg = va_arg(args, int);
	}
	va_end(args);
	return (flag);
}
