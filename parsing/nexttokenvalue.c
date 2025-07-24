/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nexttokenvalue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:35:38 by anony             #+#    #+#             */
/*   Updated: 2025/07/24 18:54:08 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_handle_pipe_token(char *input, int *ind, char **tokenvalueadress)
{
    if (!input || !ind || !tokenvalueadress)
        return (1);
    *tokenvalueadress = ft_strdup("|");
    if (!(*tokenvalueadress))
        return (1);
    (*ind)++;
    return (0);
}

int ft_handle_redirin_token(char *input, int *ind, char **tokenvalueadress)
{
    if (!input || !ind || !tokenvalueadress)
        return (1);
    if (input[(*ind) + 1] == '<')
    {
        *tokenvalueadress = ft_strdup("<<");
        if (!(*tokenvalueadress))
            return (1);
        (*ind) += 2;
    }
    else
    {
        *tokenvalueadress = ft_strdup("<");
        if (!(*tokenvalueadress))
            return (1);
        (*ind)++;
    }
    return (0);
}

int ft_handle_redirout_token(char *input, int *ind, char **tokenvalueadress)
{
    if (!input || !ind || !tokenvalueadress)
        return (1);
    if (input[(*ind) + 1] == '>')
    {
        *tokenvalueadress = ft_strdup(">>");
        if (!(*tokenvalueadress))
            return (1);
        (*ind) += 2;
    }
    else
    {
        *tokenvalueadress = ft_strdup(">");
        if (!(*tokenvalueadress))
            return (1);
        (*ind)++;
    }
    return (0);
}

int ft_handle_no_word_token(char *input, int *ind, char **tokenvalueadress)
{
    if (!input || !ind || !tokenvalueadress)
        return (1);
    if (*ind >= (int)ft_strlen(input))
        return (1);
    if (input[*ind] == '|')
    {
        if (ft_handle_pipe_token(input, ind, tokenvalueadress) != 0)
            return (1);
    }
    else if (input[*ind] == '<')
    {
        if (ft_handle_redirin_token(input, ind, tokenvalueadress) != 0)
            return (1);
    }
    else if (input[*ind] == '>')
    {
        if (ft_handle_redirout_token(input, ind, tokenvalueadress) != 0)
            return (1);
    }
    else
        return (1);
    return (0);
}

int ft_handle_word_token(char *input, int *ind, char **tokenvalueadress)
{
    int start;
    int end;

    if (!input || !ind || !tokenvalueadress)
        return (1);
    if (*ind >= (int)ft_strlen(input))
        return (1);
    start = *ind;
    while (input[*ind])
    {
        if (ft_is_quote_active(input, *ind) == 0 && (input[*ind] == '|' 
            || input[*ind] == '<' || input[*ind] == '>' || input[*ind] == ' ' 
                || (input[*ind] >= 9 && input[*ind] <= 13)))
            break ;
        (*ind)++;
    }
    end = (*ind) - 1;
    *tokenvalueadress = ft_truncate(input, start, end);
    if (!*tokenvalueadress)
        return (1);
    return (0);
}
