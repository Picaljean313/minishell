/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunb_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:07:00 by anony             #+#    #+#             */
/*   Updated: 2025/03/03 13:58:05 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printunb_fd(unsigned int i, int fd)
{
	int	count;

	count = 0;
	if (i > 9)
	{
		ft_putnbr_fd (i / 10, fd);
		ft_putchar_fd (i % 10 + 48, fd);
	}
	else
		ft_putchar_fd (i + 48, fd);
	count++;
	while (i / 10 != 0)
	{
		count++;
		i = i / 10;
	}
	return (count);
}
