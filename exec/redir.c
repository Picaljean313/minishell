/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:09:21 by anony             #+#    #+#             */
/*   Updated: 2025/08/08 20:10:35 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_redir_heredoc(t_redir *redir)
{
	int	fd;

	fd = -1;
	if (ft_last_redir_in(redir) == 1)
	{
		if (redir->type == REDIR_HEREDOC)
			fd = redir->heredocfd;
		if (fd == -1)
			return (ft_putstr_fd("heredoc failed", STDERR_FILENO), 1);
		dup2(fd, STDIN_FILENO);
		ft_close_fd(&fd);
		return (0);
	}
	if (redir->type == REDIR_HEREDOC)
		ft_close_fd(&redir->heredocfd);
	return (0);
}

int	ft_redir_input(t_redir *redir)
{
	int	fd;

	fd = -1;
	if (ft_last_redir_in(redir) == 1)
	{
		if (redir->type == REDIR_IN)
			fd = open(redir->file, O_RDONLY);
		if (fd == -1)
			return (perror("open"), -1);
		dup2(fd, STDIN_FILENO);
		ft_close_fd(&fd);
		return (0);
	}
	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
		return (perror("open"), -1);
	ft_close_fd(&fd);
	return (0);
}

int	ft_redirout(t_redir *redir)
{
	int	fd;

	if (ft_last_redir_out(redir) == 1)
	{
		if (redir->type == REDIR_OUT)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (perror("open"), 1);
		dup2(fd, STDOUT_FILENO);
		ft_close_fd(&fd);
	}
	else
	{
		fd = open(redir->file, O_WRONLY | O_CREAT, 0644);
		if (fd == -1)
			return (perror("open"), 1);
		ft_close_fd(&fd);
	}
	return (0);
}

int	ft_redir(t_redir *redir)
{
	if (!redir)
		return (0);
	while (redir)
	{
		if (redir->type == REDIR_IN)
		{
			if (ft_redir_input(redir) == -1)
				return (-1);
			if (ft_redir_input(redir) != 0)
				return (1);
		}
		if (redir->type == REDIR_HEREDOC)
			if (ft_redir_heredoc(redir) != 0)
				return (1);
		if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
			if (ft_redirout(redir) != 0)
				return (1);
		redir = redir->next;
	}
	return (0);
}
