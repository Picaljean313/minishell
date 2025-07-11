/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:48:50 by anony             #+#    #+#             */
/*   Updated: 2025/07/11 17:10:47 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
etapes :
mettre tokens avec des flags : CMD ARGS REDIR PIPE HEREDOC
remplacer les variables par leur valeur (garder $ si en fin de ligne)
*/

// t_token *ft_get_next_pipe(t_token **tab, t_token *token)
// {
//     t_token *pipe;

//     pipe = malloc (sizeof(t_token *));
//     if (token && token->type != PIPE)
//         pipe = token;
//     else
//         return (free(pipe), NULL);
//     while (token && token->type != PIPE)
//     {
//         pipe->next = 
//         token = token->next;
//     }
// }

//  ____ Faire pipe_tokens puis pipes trie

int ft_check_empty_pipes(t_token **tab)
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
    t_token *tmp;
    int cmd;
    
    cmd = 0;
    tmp = token;
    if (!tmp)
        return (1);
    while (tmp->type != PIPE)
    {
        if (tmp->type != WORD)
        {
            tmp = tmp->next;
            if (!tmp)
                return (1);
            if (tmp->type != WORD)
                return (1);
        }
        else
            cmd = 1;
        tmp = tmp->next;
        if (!tmp)
            break ;
    }
    if (cmd == 0)
        return (1);
    return (0);
}

int ft_check_pipes(t_token **tab)
{
    t_token *token;

    if (ft_check_empty_pipes(tab) != 0)
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