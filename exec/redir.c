/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:09:21 by anony             #+#    #+#             */
/*   Updated: 2025/08/08 15:31:24 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_last_redir_in(t_redir *redir)
{
	while (redir->next)
	{
		redir = redir->next;
		if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
			return (0);
	}
	return (1);
}

int	ft_redirin(t_redir *redir)
{
	int	fd;

	if (ft_last_redir_in(redir) == 1)
	{
		if (redir->type == REDIR_HEREDOC)
			fd = redir->heredocfd;
		else
			fd = open(redir->file, O_RDONLY);
		if (fd == -1)
			return (perror("open"), 1);
		dup2(fd, STDIN_FILENO);
		ft_close_fd(&fd);
		return (0);
	}
	if (redir->type == REDIR_HEREDOC)
		ft_close_fd(&redir->heredocfd);
	else
	{
		fd = open(redir->file, O_RDONLY);
		if (fd == -1)
			return (perror("open"), 1);
		ft_close_fd(&fd);
	}
	return (0);
}

int	ft_last_redir_out(t_redir *redir)
{
	while (redir->next)
	{
		redir = redir->next;
		if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
			return (0);
	}
	return (1);
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
		if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
			if (ft_redirin(redir) != 0)
				return (1);
		if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
			if (ft_redirout(redir) != 0)
				return (1);
		redir = redir->next;
	}
	return (0);
}
