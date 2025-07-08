/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:47:23 by anony             #+#    #+#             */
/*   Updated: 2025/03/03 14:01:48 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*b;
	char	*l;

	b = (char *)big;
	l = (char *)little;
	if (l[0] == '\0')
		return (b);
	i = 0;
	while (b[i] && i < len)
	{
		j = 0;
		while (b[i + j] == l[j] && b[i + j] && i + j < len)
			j++;
		if (l[j] == '\0')
			return (b + i);
		i++;
	}
	return (NULL);
}
