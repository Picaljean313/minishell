/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 19:20:21 by anony             #+#    #+#             */
/*   Updated: 2025/08/08 20:58:41 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	ft_print_after_signal(int status, int *newline, int *coredump)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
		{
			*newline = 1;
			g_signal = 130;
		}
		else if (sig == SIGQUIT)
		{
			*newline = 1;
			*coredump = 1;
			g_signal = 131;
		}
	}
	else if (WIFEXITED(status))
		g_signal = WEXITSTATUS(status);
}