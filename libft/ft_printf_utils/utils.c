/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:08:12 by anony             #+#    #+#             */
/*   Updated: 2025/03/03 13:58:02 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_puthexalower_fd(int i, int fd)
{
	if (i >= 0 && i < 10)
		ft_putchar_fd(i + 48, fd);
	else if (i == 10)
		ft_putchar_fd('a', fd);
	else if (i == 11)
		ft_putchar_fd('b', fd);
	else if (i == 12)
		ft_putchar_fd('c', fd);
	else if (i == 13)
		ft_putchar_fd ('d', fd);
	else if (i == 14)
		ft_putchar_fd('e', fd);
	else if (i == 15)
		ft_putchar_fd('f', fd);
}

void	ft_puthexaupper_fd(int i, int fd)
{
	if (i >= 0 && i < 10)
		ft_putchar_fd(i + 48, fd);
	else if (i == 10)
		ft_putchar_fd('A', fd);
	else if (i == 11)
		ft_putchar_fd('B', fd);
	else if (i == 12)
		ft_putchar_fd('C', fd);
	else if (i == 13)
		ft_putchar_fd('D', fd);
	else if (i == 14)
		ft_putchar_fd('E', fd);
	else if (i == 15)
		ft_putchar_fd('F', fd);
}

int	ft_putarg_fd(char c, va_list args)
{
	if (c == 'c')
		return (ft_printchar_fd ((char)va_arg(args, int), 1));
	if (c == 's')
		return (ft_printstr_fd (va_arg(args, char *), 1));
	if (c == 'p')
		return (ft_printptr_fd ((uintptr_t)va_arg(args, void *), 1));
	if (c == 'd' || c == 'i')
		return (ft_printnb_fd (va_arg(args, int), 1));
	if (c == 'u')
		return (ft_printunb_fd (va_arg(args, unsigned int), 1));
	if (c == 'x')
		return (ft_printhexnblow_fd (va_arg(args, unsigned int), 1));
	if (c == 'X')
		return (ft_printhexnbup_fd (va_arg(args, unsigned int), 1));
	if (c == '%')
	{
		ft_putchar_fd ('%', 1);
		return (1);
	}
	return (0);
}
