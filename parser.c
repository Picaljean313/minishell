/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:48:50 by anony             #+#    #+#             */
/*   Updated: 2025/07/11 21:07:25 by anony            ###   ########.fr       */
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



int ft_add_cmd(t_token *token, t_pipe *pipe)
{
    (void)token;
    (void)pipe;
    return (0);
}

int ft_add_redir(t_token *token, t_pipe *pipe)
{
    (void)token;
    (void)pipe;
    return (0);
}

int ft_add_arg(t_token *token, char **args, t_pipe *pipe)
{
    (void)token;
    (void)pipe;
    (void)args;
    return (0);
}




int ft_fill_pipe(t_token *token, t_pipe **pipetab)
{
    char **args;
    t_pipe *pipe;
    int cmd;

    if (!token || !pipetab)
        return (1);
    args = malloc(sizeof(char *));
    if (!args)
        return (1);
    args[0] = NULL;
    pipe = malloc(sizeof(t_pipe));
    cmd = 0;
    while (token->type != PIPE)
    {
        if (token->type == WORD && cmd ==0)
        {
            if (ft_add_cmd(token, pipe) != 0)
                return (1);
            cmd = 1;
        }
        else if (token->type == WORD && cmd == 1)
        {
            if (ft_add_arg(token, args, pipe) != 0)
                return (1);
        }
        else
        {
            if (ft_add_redir(token, pipe) != 0)
                return (1);
            token = token->next;
        }
        token = token->next;
        if (!token)
            break;
    }
    return (0);
}

t_pipe **ft_parser(t_token **tokentab)
{
    t_pipe **pipetab;
    t_token *token;

    pipetab = malloc (sizeof(t_pipe));
    if (!pipetab)
        return NULL;
    token = *tokentab;
    if (!token)
        return NULL;
    while (token)
    {
        ft_fill_pipe(token, pipetab);
        while (token->next && token->type != PIPE)
           token = token->next;
        token = token->next;
    }
    return (pipetab);
}