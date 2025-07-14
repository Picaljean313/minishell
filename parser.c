/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:48:50 by anony             #+#    #+#             */
/*   Updated: 2025/07/14 15:47:22 by anony            ###   ########.fr       */
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



int ft_add_redir(t_token *token, t_pipe *pipe)
{
    t_redir *redir;
    t_redir *tmp;
    
    redir = malloc(sizeof(t_redir));
    if (token->type == REDIR_IN || token->type == REDIR_HEREDOC)
    {
        redir->type = token->type;
        redir->file = token->next->value;
        redir->next = NULL;
        if (!pipe->redirin)
            pipe->redirin = redir;
        else
        {
            tmp = pipe->redirin;
            while (tmp->next)
                tmp = tmp->next;
            tmp->next = redir;
        }
    }
    if (token->type == REDIR_OUT || token->type == REDIR_APPEND)
    {
        redir->type = token->type;
        redir->file = token->next->value;
        redir->next = NULL;
        if (!pipe->redirout)
            pipe->redirout = redir;
        else
        {
            tmp = pipe->redirout;
            while (tmp->next)
                tmp = tmp->next;
            tmp->next = redir;
        }
    }
    return (0);
}

int ft_add_arg(t_token *token, t_pipe *pipe)
{
    int i;
    int len;
    char **args;
    
    if (!token->value)
        return (1);
    len = 0;
    if (pipe->args)
    {
        while (pipe->args[len])
            len++;
    }
    args = malloc((len + 2) * sizeof(char *));
    if (args == NULL)
        return (1);
    i = 0;
    while (i < len)
    {
        args[i] = pipe->args[i];
        i++;
    }
    args[i] = ft_strdup(token->value);
    args[i + 1] = NULL;
    free(pipe->args);
    pipe->args = args;
    return (0);
}


// a retirer
void ft_check_args(t_pipe *pipe)
{
    int i;

    i = 0;
    while (pipe->args[i])
    {
        printf("%d : %s\n", i, pipe->args[i]);
        i++;
    }
}
void ft_check_redirs(t_pipe *pipe)
{
    t_redir *tmp;

    tmp = pipe->redirin;
    while (tmp)
    {
        printf("%d : %s\n", tmp->type, tmp->file);
        tmp = tmp->next;
    }
    tmp = pipe->redirout;
    while (tmp)
    {
        printf("%d : %s\n", tmp->type, tmp->file);
        tmp = tmp->next;
    }
}


int ft_init_pipe(t_pipe *pipe)
{
    if (!pipe)
        return (1);
    pipe->cmd = NULL;
    pipe->args = NULL;
    pipe->redirin = NULL;
    pipe->redirout = NULL;
    pipe->next = NULL;
    return (0);
}

int ft_fill_pipe(t_token *token, t_pipe **pipetab)
{
    t_pipe *pipe;
    t_pipe *tmp;
    int cmd;

    if (!token || !pipetab)
        return (1);
    pipe = malloc(sizeof(t_pipe));
    if (!pipe)
        return (1);
    if (ft_init_pipe(pipe) != 0)
        return (1);
    if (!*pipetab)
        *pipetab = pipe;
    else
    {
        tmp = *pipetab;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = pipe;
    }
    cmd = 0;
    while (token->type != PIPE)
    {
        if (token->type == WORD && cmd ==0)
        {
            pipe->cmd = token->value;
            cmd = 1;
        }
        else if (token->type == WORD && cmd == 1)
        {
            if (ft_add_arg(token, pipe) != 0)
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
    printf("cmd : %s\n", pipe->cmd);
    ft_check_args(pipe);
    ft_check_redirs(pipe);
    return (0);
}

t_pipe **ft_parser(t_token **tokentab)
{
    t_pipe **pipetab;
    t_token *token;

    pipetab = malloc (sizeof(t_pipe **));
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