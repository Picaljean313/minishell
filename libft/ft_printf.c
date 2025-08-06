/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:38:56 by anony             #+#    #+#             */
/*   Updated: 2025/08/06 18:37:29 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;
	int		i;

	count = 0;
	i = 0;
	if (!str)
		return (-1);
	va_start (args, str);
	while (str[i])
	{
		if (str[i] != '%')
		{
			ft_putchar_fd (str[i], 1);
			count++;
			i++;
			continue ;
		}
		if (!str[i + 1])
			return (va_end(args), -1);
		count += ft_putarg_fd (str[i + 1], args);
		i += 2;
	}
	va_end (args);
	return (count);
}
