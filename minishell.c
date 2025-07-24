/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:52:09 by anony             #+#    #+#             */
/*   Updated: 2025/07/24 21:29:33 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int g_signal = 0;


void ft_show_tokentab(t_token *token)
{
    while (token)
    {
        printf("enum : %d\n", token->type);
        printf("value : %s\n", token->value);
        token = token->next;
    }
    return ;
}


int main (int argc, char **argv, char **envp)
{
    t_shell shell;
    int res;
    
    if (ft_check_params(argc, argv, envp) != 0)
        return (2);
    if (ft_init_shell(&shell, envp) != 0)
        return (ft_clean_shell(&shell), 2);
    ft_signal_handler();
    while (1)
    {
        res = ft_parsing(&shell);
        ft_show_tokentab(shell.tokens);
        if (res == 2)
            return (ft_clean_shell(&shell), 2);
        if (res == 1)
        {
            ft_clean_line(&shell);
            continue ;
        }
        
        ft_clean_line(&shell);
    }
    rl_clear_history();
    return (ft_clean_shell(&shell), 2);


    

        

    // }
    // 
    // ft_free_env(shell.env);
    // return (shell.exitcode);
}

