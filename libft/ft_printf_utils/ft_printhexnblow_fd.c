/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexnblow_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:51:48 by anony             #+#    #+#             */
/*   Updated: 2025/03/03 13:58:17 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printhexnblow_fd(unsigned int i, int fd)
{
	int	count;

	ft_printhexlow_fd (i, fd);
	count = 1;
	while (i / 16 != 0)
	{
		i = i / 16;
		count++;
	}
	return (count);
}
