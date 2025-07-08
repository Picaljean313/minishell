/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:45:24 by anony             #+#    #+#             */
/*   Updated: 2025/03/03 14:01:53 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		len;
	char	ch;

	len = ft_strlen(s);
	ch = (char) c;
	i = len - 1;
	if (ch == '\0')
		return ((char *)(s += len));
	while (i >= 0 && s[i] != ch)
		i--;
	if (i != -1)
		return ((char *)(s += i));
	return (NULL);
}
