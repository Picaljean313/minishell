/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:48:50 by anony             #+#    #+#             */
/*   Updated: 2025/07/10 17:25:44 by anony            ###   ########.fr       */
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