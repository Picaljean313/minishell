/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:27:22 by anony             #+#    #+#             */
/*   Updated: 2025/08/06 18:06:06 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_token(t_token *token)
{
	if (!token)
		return ;
	if (token->value)
		free(token->value);
	if (token->next)
		free(token->next);
	free(token);
	return ;
}

char	*ft_truncate(char *str, int start, int end)
{
	char	*strtrunc;
	int		i;

	if (!str || start < 0 || start > end)
		return (NULL);
	if (end > (int)ft_strlen(str) - 1)
		return (NULL);
	strtrunc = malloc ((end - start + 2) * sizeof(char));
	if (strtrunc == NULL)
		return (NULL);
	i = 0;
	while (start <= end)
	{
		strtrunc[i] = str[start];
		start++;
		i++;
	}
	strtrunc[i] = '\0';
	return (strtrunc);
}

char	*ft_getenv(char *var, char **env)
{
	int		i;
	int		len;
	char	*value;

	i = 0;
	len = ft_strlen(var);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
		{
			value = ft_strdup(env[i] + len + 1);
			return (value);
		}
		i++;
	}
	return (NULL);
}

void	ft_free_lines(t_line *lines)
{
	t_line	*temp;

	if (!lines)
		return ;
	while (lines)
	{
		temp = lines;
		lines = lines->next;
		if (temp->value)
		{
			free(temp->value);
			temp->value = NULL;
		}
		free(temp);
		temp = NULL;
	}
	return ;
}

int	ft_add_line(t_line **lines, char *value)
{
	t_line	*line;
	t_line	*temp;

	line = malloc(sizeof(t_line));
	if (!line)
		return (1);
	line->value = ft_strdup(value);
	line->next = NULL;
	if (!*lines)
		*lines = line;
	else
	{
		temp = *lines;
		while (temp->next)
			temp = temp->next;
		temp->next = line;
	}
	return (0);
}
