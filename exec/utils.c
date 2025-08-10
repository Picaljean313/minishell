/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:29:40 by anony             #+#    #+#             */
/*   Updated: 2025/08/10 17:26:19 by anony            ###   ########.fr       */
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

int	ft_exec_builtin(t_command *command, t_shell *shell, t_savedfds *fds, int sb)
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
		if (ft_exit(command, shell, fds, sb) != 0)
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
	int			newline;
	int			coredump;

	command = shell->commands;
	newline = 0;
	coredump = 0;
	while (command)
	{
		if (waitpid(command->pid, &status, 0) == -1)
			return (perror("waitpid"), 1);
		ft_print_after_signal(status, &newline, &coredump);
		command = command->next;
	}
	if (coredump == 1)
		ft_putstr_fd("Quit (core dumped)", STDOUT_FILENO);
	if (newline == 1)
		ft_putstr_fd("\n", STDOUT_FILENO);
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
