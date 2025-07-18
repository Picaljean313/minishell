/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacevars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:24:39 by anony             #+#    #+#             */
/*   Updated: 2025/07/18 18:54:17 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_replace_vars(t_shell *shell)
{
    int i;
    int start;
    int end;


    i = 0;
    while (i < (int)ft_strlen(shell->input))
    {
        if (shell->input[i] != '$' || (shell->input[i] == '$' && ft_is_simple_quote_active(shell->input, i) == 1))
            i++;
        else
        {
            if (!shell->input[i + 1])
                break;
            start = i;
            end = i;
            i++;
            if (shell->input[i] == '?')
            {
                i++;
                end = i - 1;
                if (ft_handle_var_exit_status(&shell->input, &start, &end) != 0)
                    return (1);
                continue ;
            }
            if (ft_isalpha(shell->input[i]) == 1 || shell->input[i] == '_')
            {
                i++;
                while (shell->input[i] == '_' || ft_isalnum(shell->input[i]) == 1)
                    i++;
            }   
            end = i - 1;
            if (ft_handle_var(&shell->input, &start, &end, shell->env) != 0)
                return (1);
        }
    }
    return (0);
}
