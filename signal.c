/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:23:44 by anony             #+#    #+#             */
/*   Updated: 2025/07/24 13:35:43 by anony            ###   ########.fr       */
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


void ft_signal_handler()
{
    signal(SIGINT, ft_handle_sigint);
    for (int i = 1; i < NSIG; i++) 
    {
        if (i == SIGINT)
            continue ; 
        signal(i, SIG_IGN);
    }
}