/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:53:56 by anony             #+#    #+#             */
/*   Updated: 2025/08/08 20:23:06 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_create_std_dup(t_savedfds *fds)
{
	int	savedfdout;
	int	savedfdin;
	int	savedfderr;

	savedfdin = dup(STDIN_FILENO);
	if (savedfdin == -1)
		return (1);
	savedfdout = dup(STDOUT_FILENO);
	if (savedfdout == -1)
		return (ft_close_fd(&savedfdin), 1);
	savedfderr = dup(STDERR_FILENO);
	if (savedfderr == -1)
		return (ft_close_fd(&savedfdin), ft_close_fd(&savedfdout), 1);
	fds->fdin = savedfdin;
	fds->fdout = savedfdout;
	fds->fderr = savedfderr;
	return (0);
}

void	ft_close_savedfd(t_savedfds *fds)
{
	ft_close_fd(&fds->fdin);
	ft_close_fd(&fds->fdout);
	ft_close_fd(&fds->fderr);
}

int	ft_restore_savedfd(t_savedfds *fds)
{
	if (fds->fdin != -1 && dup2(fds->fdin, STDIN_FILENO) == -1)
		return (perror("dup2 stdin"), 1);
	if (fds->fdout != -1 && dup2(fds->fdout, STDOUT_FILENO) == -1)
		return (perror("dup2 stdout"), 1);
	if (fds->fderr != -1 && dup2(fds->fderr, STDERR_FILENO) == -1)
		return (perror("dup2 stderr"), 1);
	ft_close_fd(&fds->fdin);
	ft_close_fd(&fds->fdout);
	ft_close_fd(&fds->fderr);
	return (0);
}

int	ft_exec_simple_builtin(t_command *command, t_shell *shell, t_savedfds *fds)
{
	t_redir	*redir;
	int		res;

	redir = command->redir;
	res = ft_redir(redir);
	if ( res == -1)
		return (-1);
	if ( res == 1)
		return (1);
	if (ft_exec_builtin (command, shell, fds) != 0)
		return (1);
	return (0);
}

void	ft_parent(t_exec *exec, int fd)
{
	signal(SIGINT, SIG_IGN);
	exec->prevfd = fd;
	ft_close_command_heredoc(exec->command);
	exec->command->pid = exec->pid;
}
