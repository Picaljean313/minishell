/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:23:44 by anony             #+#    #+#             */
/*   Updated: 2025/08/08 11:28:06 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sigint_main(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	g_signal = 130;
	return ;
}

void	ft_sigint_heredoc(int sig)
{
	t_hdcontext *hdctx;
	
	(void)sig;
	hdctx = ft_get_hd_ctx(NULL);
	if (hdctx)
	{
		if (hdctx->value)
			free(hdctx->value);
		if (hdctx->lines)
			ft_free_lines(hdctx->lines);
		ft_close_fd(&hdctx->fd);
		ft_clean_shell(hdctx->shell);
		free(hdctx);
	}
	g_signal = 130;
	ft_putstr_fd("\n", STDOUT_FILENO);
	exit (130);
}

void	ft_sigint_child(int sig)
{
	(void)sig;
	g_signal = 130;
	exit(130);
	return ;
}

void ft_signal_handler(t_context context)
{
	if (context == MAIN)
	{
		signal(SIGINT, ft_sigint_main);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (context == CHILD)
	{
		signal(SIGINT, ft_sigint_child);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (context == HEREDOC)
	{
		signal(SIGINT, ft_sigint_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}

// void	ft_signal_handler(t_context context)
// {
// 	int	i;

// 	ft_set_signal(context);
// 	i = 1;
// 	while (i < NSIG)
// 	{
// 		if (i != SIGINT && i != SIGQUIT && i != SIGKILL && i != SIGSTOP
// 			&& i != SIGCHLD && i != SIGPIPE
// 			&& !(i >= SIGRTMIN && i <= SIGRTMAX))
// 			signal(i, SIG_IGN);
// 		i++;
// 	}
// }
