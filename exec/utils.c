/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:29:40 by anony             #+#    #+#             */
/*   Updated: 2025/08/08 15:40:15 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_close_fd(int *fd)
{
	if (*fd == -1)
		return ;
	close(*fd);
	*fd = -1;
	return ;
}

int	ft_is_builtin(t_command *command)
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

int	ft_exec_builtin(t_command *command, t_shell *shell, t_savedfds *fds)
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
		if (ft_exit(command, shell, fds) != 0)
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

int	ft_wait_pids(t_shell *shell)
{
	t_command	*command;
	int			status;
	int			sig;

	command = shell->commands;
	while (command)
	{
		if (waitpid(command->pid, &status, 0) == -1)
			return (perror("waitpid"), 1);
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGINT)
				g_signal = 130;
			else if (sig == SIGQUIT)
				g_signal = 131;
		}
		else if (WIFEXITED(status))
			g_signal = WEXITSTATUS(status);
		command = command->next;
	}
	return (0);
}

int	ft_nb_commands(t_shell *shell)
{
	t_command	*command;
	int			nbcom;

	nbcom = 0;
	command = shell->commands;
	while (command)
	{
		command = command->next;
		nbcom++;
	}
	return (nbcom);
}
