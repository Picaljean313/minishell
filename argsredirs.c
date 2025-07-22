/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argsredirs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:41:27 by anony             #+#    #+#             */
/*   Updated: 2025/07/22 17:58:50 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_add_redirin(t_redir *redir, t_token *token, t_pipe *pipe)
{
    t_redir *tmp;
    
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

void ft_add_redirout(t_redir *redir, t_token *token, t_pipe *pipe)
{
    t_redir *tmp;
    
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

int ft_add_redir(t_token *token, t_pipe *pipe)
{
    t_redir *redir;
    
    redir = malloc(sizeof(t_redir));
    if (!redir)
        return (1);
    if (token->type == REDIR_IN || token->type == REDIR_HEREDOC)
        ft_add_redirin(redir, token, pipe);
    if (token->type == REDIR_OUT || token->type == REDIR_APPEND)
        ft_add_redirout(redir, token, pipe);
    return (0);
}

int ft_add_arg(t_token *token, t_pipe *pipe)
{
    int i;
    int len;
    char **args;
    
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
        args[i] = ft_strdup(pipe->args[i]);
        free(pipe->args[i]);
        i++;
    }
    args[i] = ft_strdup(token->value);
    args[i + 1] = NULL;
    free(pipe->args);
    pipe->args = args;
    return (0);
}
