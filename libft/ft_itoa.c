/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:08:51 by anony             #+#    #+#             */
/*   Updated: 2025/03/03 14:00:09 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n)
{
	int		len;
	long	nbr;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		nbr = n;
		nbr = -nbr;
		len++;
	}
	else
		nbr = n;
	while (nbr % 10 > 0 || nbr / 10 > 0)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

static void	ft_fill(char *str, int len, int n)
{
	long	nbr;
	int		i;

	if (n < 0)
	{
		nbr = n;
		nbr = -nbr;
	}
	else
		nbr = n;
	i = 0;
	while (i < len)
	{
		if (len - 1 - i == 0 && n < 0)
			str[len - 1 - i] = '-';
		else
		{
			str[len - 1 - i] = nbr % 10 + 48;
			nbr = nbr / 10;
		}
		i++;
	}
	str[i] = '\0';
	return ;
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	len = ft_intlen(n);
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_fill(str, len, n);
	return (str);
}
