/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacevars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:24:39 by anony             #+#    #+#             */
/*   Updated: 2025/07/21 17:25:37 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_handle_exit_and_var(t_shell *shell, int *ind)
{
    t_varlimits varlim;

    varlim.start = *ind;
    varlim.end = *ind;
    (*ind)++;
    if (shell->input[*ind] == '?')
    {
        (*ind)++;
        varlim.end = *ind - 1;
        if (ft_handle_var_exit_status(&shell->input, &varlim) != 0)
            return (1);
        return (0) ;
    }
    if (ft_isalpha(shell->input[*ind]) == 1 || shell->input[*ind] == '_')
    {
        (*ind)++;
        while (shell->input[*ind] == '_' || ft_isalnum(shell->input[*ind]) == 1)
            (*ind)++;
    }   
    varlim.end = *ind - 1;
    if (ft_handle_var(&shell->input, &varlim, shell->env) != 0)
        return (1);
    return (0);
}

int ft_replace_vars(t_shell *shell)
{
    int i;

    i = 0;
    while (i < (int)ft_strlen(shell->input))
    {
        if (shell->input[i] != '$' || (shell->input[i] == '$' && ft_is_simple_quote_active(shell->input, i) == 1))
            i++;
        else
        {
            if (!shell->input[i + 1])
                break;
            if (ft_handle_exit_and_var(shell, &i) == 1)
                return (1);
        }
    }
    return (0);
}
