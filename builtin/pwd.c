/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:06:28 by anony             #+#    #+#             */
/*   Updated: 2025/08/10 19:39:34 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_command *command)
{
	char	*cwd;

	if (!command->args || ft_strncmp(command->args[0], "pwd", 4) != 0)
		return (1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		g_signal = 1;
		return (perror("getcwd"), 1);
	}
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(cwd);
	return (g_signal = 0, 0);
}
