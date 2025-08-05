/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:23:44 by anony             #+#    #+#             */
/*   Updated: 2025/08/05 16:55:19 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

void	ft_signal_handler(void)
{
	int	i;

	signal(SIGINT, ft_handle_sigint);
	i = 1;
	while (i < NSIG)
	{
		if (i != SIGINT && i != SIGKILL && i != SIGSTOP && i != SIGCHLD
			&& i != SIGPIPE && !(i >= SIGRTMIN && i <= SIGRTMAX))
			signal(i, SIG_IGN);
		i++;
	}
}
