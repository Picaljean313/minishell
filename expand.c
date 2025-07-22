/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:13:40 by anony             #+#    #+#             */
/*   Updated: 2025/07/22 16:11:19 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int ft_expand(t_shell *shell)
{
    t_token *token;

    if (!shell->tokens)
        return (1);
    token = *shell->tokens;
    while (token)
    {
        if (ft_replace_vars(&token->value, shell) != 0)
            return (1);





            
        if (ft_remove_quotes(&token->value) != 0)
            return (1);
        printf("token:-%s-\n", token->value);
        token = token->next;
    }
    return (0);
}

