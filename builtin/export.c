/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:06:22 by anony             #+#    #+#             */
/*   Updated: 2025/08/08 17:37:33 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_var(char *var)
{
	int	i;

	if (!ft_strchr(var, '='))
		return (1);
	if (!(ft_isalpha(var[0]) == 1 || var[0] == '_'))
		return (1);
	i = 1;
	while (var[i] == '_' || ft_isalnum(var[i]) == 1)
		i++;
	if (var[i] != '=')
		return (1);
	return (0);
}

char	*ft_get_var(char *str)
{
	int		i;
	int		len;
	char	*var;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	if (!str[len])
		return (NULL);
	var = malloc ((len + 2) * sizeof(char));
	if (!var)
		return (NULL);
	i = 0;
	while (i < len + 1)
	{
		var[i] = str[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

int	ft_export(t_command *com, t_shell *shell)
{
	int		i;
	char	*var;
	char	*value;

	if (!com->args || ft_strncmp(com->args[0], "export", 7) != 0)
		return (1);
	i = 0;
	while (com->args[++i])
	{
		if (ft_check_var(com->args[i]) != 0)
		{
			g_signal = 1;
			return (ft_putstr_fd("Wrong argument\n", STDERR_FILENO), 0);
		}
		else
		{
			value = ft_strdup(ft_strchr(com->args[i], '=') + 1);
			var = ft_get_var(com->args[i]);
			if (ft_set_env_value(value, var, shell) != 0)
				return (free(value), free(var), 1);
			free(value);
			free(var);
		}
	}
	return (0);
}
