/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacevars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:24:39 by anony             #+#    #+#             */
/*   Updated: 2025/07/23 13:39:17 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_handle_exit_and_var(char **valad, int *ind, char **env)
{
    char *value;
    t_varlimits varlim;

    varlim.start = *ind;
    varlim.end = *ind;
    value = *valad;
    (*ind)++;
    if (value[*ind] == '?')
    {
        (*ind)++;
        varlim.end = *ind - 1;
        if (ft_handle_var_exit_status(valad, &varlim) != 0)
            return (1);
        return (0) ;
    }
    if (ft_isalpha(value[*ind]) == 1 || value[*ind] == '_')
    {
        (*ind)++;
        while (value[*ind] == '_' || ft_isalnum(value[*ind]) == 1)
            (*ind)++;
    }   
    varlim.end = *ind - 1;
    if (ft_handle_var(valad, &varlim, env) != 0)
        return (1);
    return (0);
}

int ft_replace_vars(char **valad, t_shell *shell)
{
    int i;

    i = 0;
    if (!valad)
        return (1);
    if (!(*valad))
        return (1);
    while (i < (int)ft_strlen(*valad))
    {
        if ((*valad)[i] != '$' || ((*valad)[i] == '$'
            && ft_is_simple_quote_active(*valad, i) == 1))
            i++;
        else
        {
            if (ft_isalpha((*valad)[i + 1]) != 1 && (*valad)[i + 1] != '_')
            {
                i++;
                continue ;
            }
            if (ft_handle_exit_and_var(valad, &i, shell->env) == 1)
                return (1);
        }
    }
    return (0);
}
