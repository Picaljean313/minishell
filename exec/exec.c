/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:27:16 by anony             #+#    #+#             */
/*   Updated: 2025/08/06 21:20:11 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_create_std_dup(t_savedfds *fds)
{
	int savedfdout;
	int savedfdin;
	int savedfderr;

	savedfdin =  dup(STDIN_FILENO);
	// if (savedfdin == -1)
	// 	return (1);
	savedfdout = dup(STDOUT_FILENO);
	// if (savedfdout == -1)
	// 	return (ft_close_fd(&savedfdin), 1);
	savedfderr = dup(STDERR_FILENO);
	// if (savedfderr == -1)
	// 	return (ft_close_fd(&savedfdin), ft_close_fd(&savedfdout), 1);
	fds->fdin = savedfdin;
	fds->fdout = savedfdout;
	fds->fderr = savedfderr;
	return (0);
}

void ft_close_savedfd(t_savedfds *fds)
{
	ft_close_fd(&fds->fdin);
	ft_close_fd(&fds->fdout);
	ft_close_fd(&fds->fderr);
}

int ft_restore_savedfd(t_savedfds *fds)
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

int ft_exec_simple_builtin(t_command *command, t_shell *shell, t_savedfds *fds)
{
	t_redir *redir;
	
	redir = command->redir;
	if (ft_redir(redir) != 0)
		return (0);
	if (ft_exec_builtin (command, shell, fds) != 0)
		return (1);
	return(0);
}

int ft_exec (t_shell *shell)
{
	int pipefd[2];
	int prevfd;
	int nbcom;
	int i;
	pid_t pid;
	char *path;
	t_command *command;
	t_savedfds fds;
    
	if (ft_create_std_dup(&fds) != 0)
		return (1);
    // si cest un builtin seul
	(void)fds;
	if (!shell->commands)
		return (1);
	if (!shell->commands->next && ft_is_builtin(shell->commands) == 0)
	{
		if (ft_exec_simple_builtin(shell->commands, shell, &fds) != 0)
			return (1);
		if (ft_restore_savedfd(&fds) != 0)
			return (1);
		g_signal = 0;
		return (0);
	}
	prevfd = -1;
	i = 0;
	command = shell->commands;
	nbcom = ft_nb_commands(shell);
	while (i < nbcom)
	{
		if (i < nbcom - 1)
			if (pipe(pipefd) == -1)
				return (perror("pipe"), 1);
		pid = fork();
		if (pid < 0)
			return (perror("fork"), 1);
        if (pid == 0)
        {
			ft_signal_handler(CHILD);
			ft_close_savedfd(&fds);
			ft_redir(command->redir);
            if (i != 0)
            {
                dup2(prevfd , STDIN_FILENO);
                ft_close_fd(&prevfd);
            }
			if (nbcom > 1)
				ft_close_fd(&pipefd[0]);
            if (i != nbcom - 1)
            {
                dup2(pipefd[1], STDOUT_FILENO);
            }
			if (nbcom > 1)
				ft_close_fd(&pipefd[1]);
			if (ft_is_builtin(command) == 0)
			{
				if (ft_exec_builtin (command, shell, &fds) != 0)
					g_signal = 2;
				else
					g_signal = 0;
				ft_close_heredoc(command);
				ft_clean_shell(shell);
				exit(g_signal);
			}
			if (!command || !command->args || !command->args[0])
			{
				ft_close_heredoc(command);
				ft_clean_shell(shell);
				exit(0);
			}
			path = ft_get_path(command, shell);
			if (!path)
			{
				ft_putstr_fd("Command not found\n", STDERR_FILENO);
				ft_close_heredoc(command);
				ft_clean_shell(shell);
				exit(127);
			}
			if (execve(path, command->args, shell->env) == -1)
            {
				perror("execve");
                free(path);
				ft_close_heredoc(command);
				ft_clean_shell(shell);
				if (errno == ENOENT)
					exit(127);
				else if (errno == EACCES || errno == ENOEXEC)
					exit(126);
				else
					exit(1);
            }
        }
        else if (pid > 0)
        {
			signal(SIGINT, SIG_IGN);
            if (i != 0)
                ft_close_fd(&prevfd);
            if (i != nbcom - 1)
                ft_close_fd(&pipefd[1]);
			prevfd = pipefd[0];
			ft_close_heredoc(command);
            command->pid = pid;
        }
        else
			return (perror("pipe"), ft_close_heredoc(command), 1);
        i++;
		command = command->next;
	}
	if (ft_wait_pids(shell) != 0)
		return (1);
	if (ft_restore_savedfd(&fds) != 0)
		return (1);
	return (0);
}

