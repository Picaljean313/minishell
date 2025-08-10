/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:02:19 by anony             #+#    #+#             */
/*   Updated: 2025/08/10 18:47:57 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_tab_len(char **tab)
{
	int	len;

	len = 0;
	while (tab[len])
		len++;
	return (len);
}

int	ft_echo(t_command *command)
{
	int	i;

	if (!command->args || ft_strncmp(command->args[0], "echo", 5) != 0)
		return (1);
	if (!command->args[1])
		return (ft_putstr_fd("\n", STDOUT_FILENO), g_signal = 0, 0);
	i = 1;
	while (ft_strncmp(command->args[i], "-n", 3) == 0)
		i++;
	while (i < ft_tab_len(command->args) - 1)
	{
		ft_putstr_fd(command->args[i], STDOUT_FILENO);
		ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (command->args[i])
	{
		ft_putstr_fd(command->args[i], STDOUT_FILENO);
		if (ft_strncmp(command->args[1], "-n", 3) != 0)
			ft_putstr_fd("\n", STDOUT_FILENO);
	}
	return (g_signal = 0, 0);
}
