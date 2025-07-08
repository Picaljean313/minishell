/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnb_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:00:27 by anony             #+#    #+#             */
/*   Updated: 2025/03/03 13:58:12 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printnb_fd(int i, int fd)
{
	int	count;

	count = 0;
	ft_putnbr_fd (i, fd);
	if (i == -2147483648)
		return (11);
	if (i < 0)
	{
		count++;
		i = -i;
	}
	count++;
	while (i / 10 != 0)
	{
		count++;
		i = i / 10;
	}
	return (count);
}
