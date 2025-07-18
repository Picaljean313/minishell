/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isquoteactive.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:29:15 by anony             #+#    #+#             */
/*   Updated: 2025/07/18 17:36:38 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_handle_simple_quote(int *sq, int *dq, int *last)
{
    if (*sq == 0 && *dq == 0)
        *sq = 1;
    else if (*sq == 1 && *dq == 0)
        *sq = 0;
    else if (*sq == 0 && *dq == 1)
    {
        *sq = 1;
        *last = '\'';
    }
    else if (*sq == 1 && *dq == 1 && *last == '\'')
    {
        *sq = 0;
        *last = '\0';
    }
    else if (*sq == 1 && *dq == 1 && *last == '\"')
    {
        *sq = 0;
        *dq = 0;
        *last = '\0';
    }
}

void ft_handle_double_quote(int *sq, int *dq, int *last)
{
    if (*sq == 0 && *dq == 0)
        *dq = 1;
    else if (*sq == 1 && *dq == 0)
    {
        *dq = 1;
        *last = '\"';
    }
    else if (*sq == 0 && *dq == 1)
        *dq = 0;
    else if (*sq == 1 && *dq == 1 && *last == '\"')
    {
        *dq = 0;
        *last = '\0';
    }
    else if (*sq == 1 && *dq == 1 && *last == '\'')
    {
        *sq = 0;
        *dq = 0;
        *last = '\0';
    }
}
