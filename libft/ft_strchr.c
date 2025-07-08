/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:24:43 by anony             #+#    #+#             */
/*   Updated: 2025/03/03 14:01:06 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	int		len;
	char	ch;

	len = ft_strlen(s);
	ch = (char)c;
	i = 0;
	if (ch == '\0')
		return ((char *)(s += len));
	while (s[i] && s[i] != ch)
		i++;
	if (i != len)
		return ((char *)(s += i));
	return (NULL);
}
