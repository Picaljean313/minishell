/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:54:29 by anony             #+#    #+#             */
/*   Updated: 2025/07/18 18:12:29 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_env(char **env)
{
    int i;

    if (!env)
        return ;
    i = 0;
    while (env[i])
    {
        free(env[i]);
        i++;
    }
    free(env);
    return ;
}

void ft_free_token_tab(t_token **tokentab)
{
    int i;

    if (!tokentab)
        return ;
    i = 0;
    while (tokentab[i])
    {
        free(tokentab[i]);
        i++;
    }
    free(tokentab);
    return ;
}

void ft_clean_shell(t_shell *shell)
{
    ft_free_env(shell->env);
    ft_free_token_tab(shell->tokens);
    return ;
}