/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:18:57 by anony             #+#    #+#             */
/*   Updated: 2025/03/03 13:59:16 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_getstart(char const *s1, char const *set)
{
	int	start;

	start = 0;
	while (ft_check(s1[start], set))
		start++;
	return (start);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*str;
	int		i;

	start = ft_getstart(s1, set);
	i = 0;
	while (s1[i])
		i++;
	if (start == i)
		return (ft_strdup(""));
	end = i - 1;
	while (ft_check(s1[end], set))
		end--;
	str = malloc((end - start + 2) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (start + i <= end)
	{
		str[i] = s1[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
