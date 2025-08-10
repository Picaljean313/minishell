/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 21:35:18 by anony             #+#    #+#             */
/*   Updated: 2025/08/10 23:52:21 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_add_export_value(char *value, t_shell *shell)
{
	char	**newexport;
	int		i;
	int		len;

	if (!shell->export)
		return (1);
	len = 0;
	while (shell->export[len])
		len++;
	newexport = malloc ((len + 2) * sizeof(char *));
	if (!newexport)
		return (1);
	i = 0;
	while (i < len)
	{
		newexport[i] = shell->export[i];
		i++;
	}
	newexport[i] = value;
	i++;
	newexport[i] = NULL;
	free(shell->export);
	shell->export = newexport;
	return (0);
}

int	ft_set_export_no_value(char *var, t_shell *shell)
{
	int		i;
	char	*value;
    int     len;

	if (!var)
		return (1);
	value = ft_strjoin("declare -x ", var);
	if (!value)
		return (1);
    len = (int)ft_strlen(value);
	i = 0;
	while (shell->export[i])
	{
		if (ft_strncmp(shell->export[i], value, len) == 0
            && (!shell->export[i][len]
            || shell->export[i][len] == '='))
            return (free(value), 0);
		i++;
	}
	if (ft_add_export_value(value, shell) != 0)
		return (free(value), 1);
	return (0);
}

char	*ft_get_export_var(char *str)
{
	int		i;
	int		len;
	char	*var;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	if (!str[len])
		return (NULL);
	var = malloc ((len + 1) * sizeof(char));
	if (!var)
		return (NULL);
	i = 0;
	while (i < len)
	{
		var[i] = str[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

char *ft_get_value(char *arg)
{
	char	*var;
    char    *value;

	if (!arg)
		return (NULL);
    var = ft_get_export_var(arg);
    if (!var)
        return (NULL);
    value = ft_strjoin("declare -x ", var);
    free(var);
    if (!value)
        return (NULL);
    return (value);
}

int	ft_set_export_value(char *arg, t_shell *shell)
{
    char    *value;
    int     i;

    value = ft_get_value(arg);
    if (!value)
        return (1);
    i = -1;
	while (shell->export[++i])
	{
		if (ft_strncmp(shell->export[i], value, (int)ft_strlen(value)) == 0
            && (!shell->export[i][(int)ft_strlen(value)]
            || shell->export[i][(int)ft_strlen(value)] == '='))
            {
                free(shell->export[i]);
                shell->export[i] = ft_create_export_var(arg);
                if (ft_replace_env_var(arg, shell) != 0)
                    return (free(value), 1);
                return (free(value), 0);
            }
	}
	if (ft_add_export_value(value, shell) != 0)
		return (free(value), 1);
    if (ft_replace_env_var(arg, shell) != 0)
        return (free(value), 1);
    return (0);
}
