/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:23:38 by anony             #+#    #+#             */
/*   Updated: 2025/07/24 19:41:36 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void ft_remove_empty_tokens(t_shell *shell)
// {
//     t_token *token;
//     t_token *temp;

//     token = shell->tokens;
//     while (ft_strncmp(token->value, "", 1) == 0)
//     {
//         if (token->next)
//             token = token->next;
//         else
//         {
//             shell->tokens = NULL;
//             return ;
//         }
//     }
//     shell->tokens = token;
//     while (token)
//     {
//         temp = token->next;
//         if (temp)
//         {
//             if (ft_strncmp(temp->value, "", 1) == 0)
//                 temp = temp->next;
//         }
//         else
//             break;
//     }
//     bouf
// }

int ft_expand(t_shell *shell)
{
    t_token *token;

    if (!shell->tokens)
        return (1);
    token = shell->tokens;
    while (token)
    {
        if (!token->value)
            return (1);
        if (ft_replace_vars(&token->value, shell) != 0)
            return (1);
        if (ft_remove_quotes(&token->value) != 0)
            return (1);
        token = token->next;
    }
    // ft_remove_empty_tokens(shell);
    return (0);
}
