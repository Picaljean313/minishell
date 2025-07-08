/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalhandler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:07:35 by anony             #+#    #+#             */
/*   Updated: 2025/07/08 19:59:10 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void ft_handle_sigint(int sig)
{
    (void)sig;
    
    rl_replace_line("", 0);
    write(1, "\n", 1);
    rl_on_new_line();
    rl_redisplay();
    return ;
}

void ft_handle_sigquit(int sig)
{
    (void)sig;
}

void ft_signal_handler()
{
    signal(SIGINT, ft_handle_sigint);
    signal(SIGQUIT, ft_handle_sigquit);
    for (int i = 1; i < NSIG; i++) 
    {
        if (i == SIGINT || i == SIGQUIT)
            continue ; 
        signal(i, SIG_IGN);
    }
}