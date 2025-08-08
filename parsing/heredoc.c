/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 17:52:54 by anony             #+#    #+#             */
/*   Updated: 2025/08/08 21:06:58 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_handle_heredoc_line(t_ctxt *hdctx, char *lim)
{
	hdctx->value = readline("> ");
	if (!hdctx->value)
		return (1);
	if ((lim && lim[0] == '\0' && hdctx->value[0] == '\0')
		|| ft_strncmp(hdctx->value, lim, ft_strlen(lim) + 1) == 0)
	{
		free(hdctx->value);
		hdctx->value = NULL;
		return (1);
	}
	if (ft_add_line(&hdctx->lines, hdctx->value) != 0)
	{
		ft_free_heredoc_context(hdctx);
		exit(2);
	}
	free(hdctx->value);
	hdctx->value = NULL;
	return (0);
}

int	ft_fill_heredoc(char *lim, int fd, t_shell *shell)
{
	t_line	*temp;
	t_ctxt	*hdctx;

	hdctx = malloc(sizeof(t_ctxt));
	hdctx->value = NULL;
	hdctx->lines = NULL;
	hdctx->fd = fd;
	hdctx->shell = shell;
	ft_get_hd_ctx(hdctx);
	ft_signal_handler(HEREDOC);
	while (1)
	{
		if (ft_handle_heredoc_line(hdctx, lim) == 1)
			break ;
	}
	temp = hdctx->lines;
	while (temp)
	{
		ft_putstr_fd(temp->value, fd);
		ft_putstr_fd("\n", fd);
		temp = temp->next;
	}
	ft_free_heredoc_context(hdctx);
	exit(0);
}

int	ft_heredoc(char *lim, t_shell *shell)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		ft_close_fd(&pipefd[0]);
		ft_fill_heredoc(lim, pipefd[1], shell);
	}
	signal(SIGINT, SIG_IGN);
	ft_close_fd(&pipefd[1]);
	if (waitpid(pid, &status, 0) == -1)
		return (perror("waitpid"), ft_close_fd(&pipefd[0]), -1);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		return (g_signal = 130, ft_close_fd(&pipefd[0]), -1);
	return (pipefd[0]);
}

int	ft_handle_heredocs(t_shell *shell)
{
	t_command	*command;
	t_redir		*redir;

	if (!shell->commands)
		return (1);
	command = shell->commands;
	while (command)
	{
		redir = command->redir;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
			{
				redir->heredocfd = ft_heredoc(redir->file, shell);
				if (redir->heredocfd == -1)
					return (1);
			}
			redir = redir->next;
		}
		command = command->next;
	}
	return (0);
}
