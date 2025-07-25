/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:58:06 by anony             #+#    #+#             */
/*   Updated: 2025/07/25 19:49:10 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_params(int argc, char **argv, char **env)
{
	if (argc != 1 || !argv || !env)
	{
		printf("Check params");
		return (1);
	}
	return (0);
}

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
			newlvl = ft_itoa(lvl);
			if (!newlvl)
				return (1);
			free(env[i]);
			env[i] = ft_strjoin("SHLVL=", newlvl);
			if (!env[i])
			{
				env[i] = ft_strdup("");
				return (free(newlvl), 1);
			}
			return (free(newlvl), 0);
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
	if (ft_set_shlvl(env_copy) != 0)
		return (NULL);
	return (env_copy);
}

int	ft_init_shell(t_shell *shell, char **envp)
{
	shell->env = ft_set_env(envp);
	if (!shell->env)
		return (1);
	shell->input = NULL;
	shell->exitcode = 0;
	shell->tokens = NULL;
	shell->commands = NULL;
	return (0);
}
