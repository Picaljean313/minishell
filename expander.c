/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:40:12 by anony             #+#    #+#             */
/*   Updated: 2025/07/14 18:15:40 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_replace_var(char *value)
{
    char *newvalue;
    char *var;
    int i;
    
    if (!value)
        return (NULL);
    if (value[0] == '\'')
        return (value);
    i = 0;
    while (ft_strchr(value, '$'))
    {
        value = ft_strchr(value, '$');
    }
}

int ft_expand(t_token **tokentab)
{
    t_token *token;

    if (!*tokentab)
        return (1);
    token = *tokentab;
    while (token)
    {
        if (ft_replace_var(token->value) != 0)
            return (1);
        token->next;
    }
    return (0);
}