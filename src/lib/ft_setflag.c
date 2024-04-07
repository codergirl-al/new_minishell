/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setflag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 19:09:31 by ykerdel           #+#    #+#             */
/*   Updated: 2024/04/07 19:09:48 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib.h"

int	ft_setflag(int flag, ...)
{
	va_list	args;
	int		arg;

	va_start(args, flag);
	arg = va_arg(args, int);
	while (arg != 0)
		if (!(flag & arg))
			flag |= arg;
	va_end(args);
	return (flag);
}
