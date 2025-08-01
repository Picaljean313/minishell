/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleredirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:03:28 by anony             #+#    #+#             */
/*   Updated: 2025/08/01 22:46:27 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_last_redir(t_redir *redir)
{
    t_type type;

    type = redir->type;
    while (redir->next)
    {
        redir = redir->next;
        if (redir->type == type)
            return (0);
    }
    return (1);
}

int ft_handle_redir(t_command *command)
{
    t_redir *redir;
    int fd;

    if (!command->redir)
        return (0);
    redir = command->redir;
    while (redir)
    {
        if (redir->type == REDIR_IN) {
            fd = open(redir->file, O_RDONLY);
            dup2(fd, command->fdin);    
            command->fdin = fd;
            ft_close_fd(&fd);
        }
        else if (redir->type == REDIR_OUT) {
            if (ft_last_redir(redir) == 1)
            {
                fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd == -1)
                {
                    perror("open");
                    exit(2);
                }
                dup2(fd, STDOUT_FILENO);
                ft_close_fd(&fd);
                // ft_close_fd(&command->fdout);
                // command->fdout = fd;
            }
            else
            {
                fd = open(redir->file, O_WRONLY | O_CREAT, 0644);
                if (fd == -1)
                {
                    perror("open");
                    exit(2);
                }
                ft_close_fd(&fd);
                // command->fdout = fd;
            }
        }
        else if (redir->type == REDIR_APPEND) {
            fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            dup2(fd,  command->fdout);
            command->fdout = fd;
            ft_close_fd(&fd);
        }
        else if (redir->type == REDIR_HEREDOC) {
            fd = ft_heredoc(redir->file);
            dup2(fd,  command->fdin);
            command->fdin = fd;
            ft_close_fd(&fd);
        }
        redir = redir->next;
    }
    return(0); // a vrirer apres avoir tout gere
}

/*
À propos de [?2004h

Ce caractère vient du mode bracketed paste (2004h) activé par certains shells ou readline. Il est écrit si tu rediriges stdout trop tôt, avant readline() ou les fonctions qui affichent le prompt.

Donc si dup2(fd, STDOUT_FILENO) est fait trop tôt, le prompt ou les séquences de contrôle se retrouvent dans ton fichier (comme txt2 dans ton cas).
*/