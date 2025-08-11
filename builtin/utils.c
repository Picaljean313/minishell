/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:59:46 by anony             #+#    #+#             */
/*   Updated: 2025/08/11 15:05:08 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_add_env_value(char *value, t_shell *shell)
{
	char	**newenv;
	int		i;
	int		len;

	if (!shell->env)
		return (1);
	len = 0;
	while (shell->env[len])
		len++;
	newenv = malloc ((len + 2) * sizeof(char *));
	if (!newenv)
		return (1);
	i = 0;
	while (i < len)
	{
		newenv[i] = shell->env[i];
		i++;
	}
	newenv[i] = value;
	i++;
	newenv[i] = NULL;
	free(shell->env);
	shell->env = newenv;
	return (0);
}

void	ft_fill_export_var(char *newval, char *value, int i, int len)
{
	while (value[i] && value[i] != '=')
	{
		newval[len] = value[i];
		len++;
		i++;
	}
	newval[len] = '=';
	newval[++len] = '\"';
	len++;
	i++;
	while (value[i])
	{
		newval[len] = value[i];
		len++;
		i++;
	}
	newval[len] = '\"';
	newval[++len] = '\0';
}

char	*ft_create_export_var(char *value)
{
	char	*newval;
	int		i;
	int		len;
	char	*suffix;

	suffix = "declare -x ";
	len = (int)ft_strlen(value) + 14;
	newval = malloc(len * sizeof(char));
	if (!newval)
		return (NULL);
	len = 0;
	i = 0;
	while (suffix[len])
	{
		newval[len] = suffix[len];
		len++;
	}
	ft_fill_export_var(newval, value, i, len);
	return (newval);
}
