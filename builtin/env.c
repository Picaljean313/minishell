/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:06:08 by anony             #+#    #+#             */
/*   Updated: 2025/08/10 19:26:57 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_command *command, t_shell *shell)
{
	int	i;

	if (!command->args || ft_strncmp(command->args[0], "env", 4) != 0)
		return (1);
	if (command->args[1])
	{
		ft_putstr_fd("No such file or directory\n", STDOUT_FILENO);
		g_signal = 127;
		return (0);
	}
	i = 0;
	if (!shell->env)
		return (g_signal = 0, 0);
	while (shell->env[i])
	{
		if (ft_strchr(shell->env[i], '='))
		{
			ft_putstr_fd(shell->env[i], STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		i++;
	}
	return (g_signal = 0, 0);
}
