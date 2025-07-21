/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkpipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:36:25 by anony             #+#    #+#             */
/*   Updated: 2025/07/21 17:52:25 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int ft_check_empty_pipe(t_token **tab)
{
    t_token *token;

    if (!*tab)
        return(1);
    token = *tab;
    if (token->type == PIPE)
        return(1);
    while (token->next)
        token = token->next;
    if (token->type == PIPE)
        return(1);
    return (0);
}

int ft_check_pipe(t_token *token)
{
    int cmd;
    
    cmd = 0;
    while (token->type != PIPE)
    {
        if (token->type != WORD)
        {
            token = token->next;
            if (!token)
                return (1);
            if (token->type != WORD)
                return (1);
        }
        else
            cmd = 1;
        token = token->next;
        if (!token)
            break ;
    }
    if (cmd == 0)
        return (1);
    return (0);
}

int ft_check_pipes(t_token **tab)
{
    t_token *token;

    if (ft_check_empty_pipe(tab) != 0)
        return (1);
    token = *tab;
    while (token)
    {
        if (ft_check_pipe(token) != 0)
            return (1);
        while (token->next && token->type != PIPE)
           token = token->next;
        token = token->next;
    }
    return (0);
}
