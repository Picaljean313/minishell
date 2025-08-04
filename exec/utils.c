/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:29:40 by anony             #+#    #+#             */
/*   Updated: 2025/08/04 22:53:42 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_close_fd(int *fd)
{
	if (*fd == -1)
		return ;
	close(*fd);
	*fd = -1;
	return ;
}

int ft_is_builtin(t_command *command)
{
    if (!command->args)
		return (1);
	if (ft_strncmp(command->args[0], "echo", 5) == 0)
		return (0);
	if (ft_strncmp(command->args[0], "cd", 3) == 0)
		return (0);
	if (ft_strncmp(command->args[0], "pwd", 4) == 0)
		return (0);
	if (ft_strncmp(command->args[0], "export", 7) == 0)
		return (0);
	if (ft_strncmp(command->args[0], "unset", 6) == 0)
		return (0);
	if (ft_strncmp(command->args[0], "env", 4) == 0)
		return (0);
	if (ft_strncmp(command->args[0], "exit", 5) == 0)
		return (0);
    return (1);
}


int ft_exec_builtin(t_command *command, t_shell *shell)
{
    if (!command->args)
		return (2);
	if (ft_strncmp(command->args[0], "cd", 3) == 0)
		if (ft_cd(command, shell) != 0)
			return (1);
	if (ft_strncmp(command->args[0], "echo", 5) == 0)
		if (ft_echo(command) != 0)
			return (1);
	if (ft_strncmp(command->args[0], "env", 4) == 0)
		if (ft_env(command, shell) != 0)
			return (1);
	if (ft_strncmp(command->args[0], "exit", 5) == 0)
		if (ft_exit(command) != 0)
			return (1);
	if (ft_strncmp(command->args[0], "export", 7) == 0)
		if (ft_export(command, shell) != 0)
			return (1);
	if (ft_strncmp(command->args[0], "pwd", 4) == 0)
		if (ft_pwd(command) != 0)
			return (1);
	if (ft_strncmp(command->args[0], "unset", 6) == 0)
		if (ft_unset(command, shell) != 0)
			return (1);
    return (0);
}
