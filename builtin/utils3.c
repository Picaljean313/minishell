/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 23:08:18 by anony             #+#    #+#             */
/*   Updated: 2025/08/11 15:08:42 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_replace_env_var(char *arg, t_shell *shell)
{
	char	*value;
	char	*var;

	value = ft_strdup(ft_strchr(arg, '=') + 1);
	var = ft_get_var(arg);
	if (ft_set_env_value(value, var, shell) != 0)
		return (free(value), free(var), 1);
	free(value);
	free(var);
	return (0);
}

int	ft_check_unset_var(char *var)
{
	int	i;

	if (!(ft_isalpha(var[0]) == 1 || var[0] == '_'))
		return (1);
	i = 1;
	while (var[i] == '_' || ft_isalnum(var[i]) == 1)
		i++;
	if (var[i] != '\0')
		return (1);
	return (0);
}
