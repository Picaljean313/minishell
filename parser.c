/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:20:00 by anony             #+#    #+#             */
/*   Updated: 2025/07/22 19:56:22 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe **ft_parser(t_token **tokentab)
{
    t_pipe **pipetab;
    t_token *token;

    if (!tokentab)
        return (NULL);
    pipetab = malloc (sizeof(t_pipe *));
    if (!pipetab)
        return (NULL);
    *pipetab = NULL;
    token = *tokentab;
    if (!token)
        return (NULL);
    while (token)
    {
        ft_fill_pipe(token, pipetab);
        while (token->next && token->type != PIPE)
           token = token->next;
        token = token->next;
    }
    return (pipetab);
}
