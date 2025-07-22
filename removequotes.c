/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removequotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:23:19 by anony             #+#    #+#             */
/*   Updated: 2025/07/22 16:29:06 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_handle_quote(char **valad, int start, int end)
{
    char *value;
    char *newvalue;
    int newlen;
    int i;

    value = *valad;
    newlen = (int)ft_strlen(value) - 2;
    if (newlen < 0)
        return (1);
    newvalue = malloc ((newlen + 1) * sizeof(char));
    i = 0;
    while (i < start)
    {
        newvalue[i] = value[i];
        i++;
    }
    i++;
    while (i < end)
    {
        newvalue[i - 1] = value[i];
        i++;
    }
    i++;
    while (i < (int)ft_strlen(value))
    {
        newvalue[i - 2] = value[i];
        i++;
    }
    newvalue[i - 2] = '\0';
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
            if (!(*valad)[end] || ft_handle_quote(valad, start, end) != 0)
                return (1);
            start = end - 1;
        }
        else
            start++;
    }
    return (0);
}
