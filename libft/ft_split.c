/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:44:22 by anony             #+#    #+#             */
/*   Updated: 2025/03/03 14:00:57 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char const *s, char c)
{
	int	i;
	int	words_nb;

	i = 0;
	words_nb = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			words_nb++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (words_nb);
}

static void	ft_free(int nb, char **tab)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		free(tab[i]);
		i++;
	}
	return ;
}

static int	ft_getword(const char *s, char c, int pos, char **tab)
{
	int		len;
	char	*word;
	int		i;

	len = 0;
	while (s[pos + len] && s[pos + len] != c)
		len++;
	word = malloc((len + 1) * sizeof(char));
	if (word == NULL)
		return (0);
	i = 0;
	while (i < len)
	{
		word[i] = s[pos + i];
		i++;
	}
	word[len] = '\0';
	tab[0] = word;
	return (1);
}

static int	ft_fill(const char *s, char c, char **tab)
{
	int	i;
	int	word_pos;

	i = 0;
	word_pos = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			if (ft_getword(s, c, i, tab + word_pos) == 0)
			{
				if (word_pos > 0)
					ft_free(word_pos, tab);
				return (0);
			}
			word_pos++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	tab = malloc((ft_count(s, c) + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	if (ft_fill(s, c, tab) == 0)
	{
		free(tab);
		return (NULL);
	}
	tab[ft_count(s, c)] = NULL;
	return (tab);
}
