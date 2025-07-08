/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:02:16 by anony             #+#    #+#             */
/*   Updated: 2025/03/03 13:58:09 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_printhexlow_fd(uintptr_t i, int fd)
{
	if (i > 15)
	{
		ft_printhexlow_fd (i / 16, fd);
		ft_puthexalower_fd (i % 16, fd);
	}
	else
		ft_puthexalower_fd (i, fd);
}

int	ft_printptr_fd(uintptr_t i, int fd)
{
	int	count;

	if (i == 0)
	{
		ft_putstr_fd ("(nil)", fd);
		return (5);
	}
	ft_putstr_fd ("0x", fd);
	ft_printhexlow_fd (i, fd);
	count = 2;
	count++;
	while (i / 16 != 0)
	{
		i = i / 16;
		count++;
	}
	return (count);
}
