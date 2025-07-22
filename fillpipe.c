/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillpipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:26:01 by anony             #+#    #+#             */
/*   Updated: 2025/07/22 18:15:17 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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

int ft_fill_pipe_bis(t_token *token, t_pipe *pipe)
{
    int cmd;

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
    return (0);
}

// a virer
void ft_check_args(t_pipe *pipe)
{
    int i;

    i = 0;
    if (!pipe->args)
        return ;
    while (pipe->args[i])
    {
        printf("%d : %s\n", i, pipe->args[i]);
        i++;
    }
}

// a virer
void ft_check_redirs(t_pipe *pipe)
{
    t_redir *tmp;

    tmp = pipe->redirin;
    while (tmp)
    {
        printf("%d in: %s\n", tmp->type, tmp->file);
        tmp = tmp->next;
    }
    tmp = pipe->redirout;
    while (tmp)
    {
        printf("%d out: %s\n", tmp->type, tmp->file);
        tmp = tmp->next;
    }
}



int ft_fill_pipe(t_token *token, t_pipe **pipetab)
{
    t_pipe *pipe;
    t_pipe *tmp;

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
    if (ft_fill_pipe_bis(token, pipe) != 0)
        return (1);
    printf("cmd : %s\n", pipe->cmd);
    ft_check_args(pipe);
    ft_check_redirs(pipe);
    return (0);
}
