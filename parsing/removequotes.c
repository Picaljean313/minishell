/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removequotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:23:19 by anony             #+#    #+#             */
/*   Updated: 2025/07/24 17:54:05 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_handle_quote_bis(char **valad, int start, int end, char *newvalue)
{
    int i;
    
    i = 0;
    while (i < start)
    {
        newvalue[i] = (*valad)[i];
        i++;
    }
    i++;
    while (i < end)
    {
        newvalue[i - 1] = (*valad)[i];
        i++;
    }
    i++;
    while (i < (int)ft_strlen(*valad))
    {
        newvalue[i - 2] = (*valad)[i];
        i++;
    }
    newvalue[i - 2] = '\0';
    return ;
}

int ft_handle_quote(char **valad, int start, int end)
{
    char *newvalue;
    int newlen;

    if (!(*valad)[end])
        return (1);
    newlen = (int)ft_strlen(*valad) - 2;
    if (newlen < 0)
        return (1);
    newvalue = malloc ((newlen + 1) * sizeof(char));
    if (!newvalue)
        return (1);
    ft_handle_quote_bis(valad, start, end, newvalue);
    free(*valad);
    *valad = newvalue;
    return (0);
}

int ft_remove_quotes(char **valad)
{
    int start;
    int end;
    char quote;

    start = 0;
    while ((*valad)[start])
    {
        if ((*valad)[start] == '\"' || (*valad)[start] == '\'')
        {
            if ((*valad)[start] == '\"')
                quote = '\"';
            else
                quote = '\'';
            end = start;
            end++;
            while ((*valad)[end] && (*valad)[end] != quote)
                end++;
            if (ft_handle_quote(valad, start, end) != 0)
                return (1);
            start = end - 1;
        }
        else
            start++;
    }
    return (0);
}
