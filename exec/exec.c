/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:27:16 by anony             #+#    #+#             */
/*   Updated: 2025/08/08 20:45:38 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exec_child(t_shell *shell, t_exec *exec)
{
	exec->path = ft_get_path(exec->command, shell);
	if (!exec->path)
	{
		ft_putstr_fd("Command not found\n", STDERR_FILENO);
		ft_close_heredoc(shell);
		ft_clean_shell(shell);
		free(exec);
		exit(127);
	}
	if (execve(exec->path, exec->command->args, shell->env) == -1)
	{
		perror("execve");
		free(exec->path);
		ft_close_heredoc(shell);
		ft_clean_shell(shell);
		if (errno == ENOENT)
			return (free(exec), exit(127));
		else if (errno == EACCES || errno == ENOEXEC)
			return (free(exec), exit(126));
		else
			return (free(exec), exit(1));
	}
}

void	ft_child(t_shell *shell, t_exec *exec, t_savedfds *fds)
{
	ft_signal_handler(CHILD);
	ft_close_savedfd(fds);
	if (ft_is_builtin(exec->command) == 0)
	{
		if (ft_exec_builtin (exec->command, shell, fds) != 0)
			g_signal = 2;
		else
			g_signal = 0;
		ft_close_heredoc(shell);
		ft_clean_shell(shell);
		free(exec),
		exit(g_signal);
	}
	if (!exec->command || !exec->command->args || !exec->command->args[0])
	{
		ft_close_heredoc(shell);
		ft_clean_shell(shell);
		free(exec),
		exit(0);
	}
	ft_exec_child(shell, exec);
}

int	ft_fork(t_shell *shell, t_exec *exec, t_savedfds *fds)
{
	int	pipefd[2];

	if (exec->i < exec->nbcom - 1)
		if (pipe(pipefd) == -1)
			return (perror("pipe"), 1);
	exec->pid = fork();
	if (exec->pid < 0)
		return (perror("fork"), 1);
	if (exec->pid == 0)
	{
		ft_child_redir(shell, exec, fds);
		if (exec->nbcom > 1 && exec->i < exec->nbcom - 1)
			ft_close_fd(&pipefd[0]);
		if (exec->i != exec->nbcom - 1)
			if (ft_has_output_redir(exec->command->redir) != 0)
				dup2(pipefd[1], STDOUT_FILENO);
		if (exec->nbcom > 1 && exec->i < exec->nbcom - 1)
			ft_close_fd(&pipefd[1]);
		ft_child(shell, exec, fds);
	}
	if (exec->i != 0)
		ft_close_fd(&exec->prevfd);
	if (exec->i != exec->nbcom - 1)
		ft_close_fd(&pipefd[1]);
	return (ft_parent(exec, pipefd[0]), 0);
}

int	ft_exec_commands(t_shell *shell, t_exec *exec, t_savedfds *fds)
{
	if (!exec->command)
		return (1);
	while (exec->i < exec->nbcom)
	{
		if (ft_fork(shell, exec, fds) != 0)
			return (1);
	exec->i++;
		exec->command = exec->command->next;
	}
	if (ft_wait_pids(shell) != 0)
		return (1);
	ft_close_heredoc(shell);
	if (ft_restore_savedfd(fds) != 0)
		return (1);
	return (0);
}

// void ft_show(t_command *command)
// {
// 	t_redir *redir;

// 	redir = command->redir;
// 	while (redir)
// 	{
// 		printf("type:%d, fd:%d\n", redir->type, redir->heredocfd);
// 		redir = redir->next;
// 	}
// }

int	ft_exec(t_shell *shell)
{
	t_savedfds	fds;
	t_exec		*exec;

	exec = malloc(sizeof(t_exec));
	if (!exec)
		return (1);
	ft_init_exec(exec, shell);
	if (ft_create_std_dup(&fds) != 0)
		return (free(exec), 1);
	if (!shell->commands)
		return (ft_close_savedfd(&fds), free(exec), 1);
	if (!shell->commands->next && ft_is_builtin(shell->commands) == 0)
		return (free(exec), ft_simple_builtin(shell, &fds));
	if (ft_exec_commands(shell, exec, &fds) != 0)
		return (ft_close_savedfd(&fds), free(exec), 1);
	return (free(exec), 0);
}
