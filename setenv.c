/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:15:13 by anony             #+#    #+#             */
/*   Updated: 2025/07/18 14:55:38 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_set_shlvl(char **env)
{
	int		i;
	int		lvl;
	char	*newlvl;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
		{
			lvl = ft_atoi(env[i] + 6) + 1;
			free(env[i]);
			newlvl = ft_itoa(lvl);
			if (!newlvl)
				return (1);
			env[i] = ft_strjoin("SHLVL=", newlvl);
			if (!env[i])
				return (free(newlvl), 1);
			free(newlvl);
			return (0);
		}
		i++;
	}
	return (0);
}

char	**ft_set_env(char **env)
{
	int		i;
	int		j;
	char	**env_copy;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i])
		i++;
	env_copy = malloc ((i + 1) * sizeof(char *));
	if (!env_copy)
		return (NULL);
	j = 0;
	while (j < i)
	{
		env_copy[j] = ft_strdup(env[j]);
		if (!env_copy[j])
			return (NULL);
		j++;
	}
	env_copy[j] = NULL;
	ft_set_shlvl(env_copy);
	return (env_copy);
}