/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexnbup_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:58:07 by anony             #+#    #+#             */
/*   Updated: 2025/03/03 13:58:15 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_printhexup_fd(uintptr_t i, int fd)
{
	if (i > 15)
	{
		ft_printhexup_fd (i / 16, fd);
		ft_puthexaupper_fd (i % 16, fd);
	}
	else
		ft_puthexaupper_fd (i, fd);
}

int	ft_printhexnbup_fd(unsigned int i, int fd)
{
	int	count;

	ft_printhexup_fd (i, fd);
	count = 1;
	while (i / 16 != 0)
	{
		i = i / 16;
		count++;
	}
	return (count);
}
