/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:53:18 by anony             #+#    #+#             */
/*   Updated: 2025/08/10 19:24:13 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_simple_builtin(t_shell *shell, t_savedfds *fds)
{
	int	res;

	res = ft_exec_simple_builtin(shell->commands, shell, fds);
	if (res != 0)
	{
		ft_close_heredoc(shell);
		if (ft_restore_savedfd(fds) != 0)
			return (1);
		if (res == -1)
			return (g_signal = 1, 0);
		return (1);
	}
	ft_close_heredoc(shell);
	if (ft_restore_savedfd(fds) != 0)
		return (1);
	return (0);
}

void	ft_init_exec(t_exec *exec, t_shell *shell)
{
	exec->nbcom = ft_nb_commands(shell);
	exec->path = NULL;
	exec->pid = -1;
	exec->prevfd = -1;
	exec->i = 0;
	exec->command = shell->commands;
}

int	ft_has_output_redir(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
			return (0);
		redir = redir->next;
	}
	return (1);
}

int	ft_has_input_redir(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
			return (0);
		redir = redir->next;
	}
	return (1);
}

void	ft_child_redir(t_shell *shell, t_exec *exec, t_savedfds *fds)
{
	ft_signal_handler(CHILD);
	ft_close_savedfd(fds);
	if (ft_redir(exec->command->redir) != 0)
	{
		g_signal = 1;
		ft_close_heredoc(shell);
		ft_clean_shell(shell);
		exit (1);
	}
	if (exec->i != 0)
	{
		if (ft_has_input_redir(exec->command->redir) != 0)
			dup2(exec->prevfd, STDIN_FILENO);
		ft_close_fd(&exec->prevfd);
	}
}
