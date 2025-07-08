/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:44:51 by anony             #+#    #+#             */
/*   Updated: 2025/07/08 20:03:57 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_add_token(t_token **tab, t_token_type type, char *value)
{
    t_token *token;
    t_token *temp;

    token = malloc(sizeof(t_token));
    token->type = type;
    token->value = ft_strdup(value);
    token->next = NULL;
    if (!*tab)
        *tab = token;
    else
    {
        temp = *tab;
        while (temp->next)
            temp = temp->next;
        temp->next = token;
    }
}

int ft_check_wrong_operator(char *input)
{
    size_t len;

    len = ft_strlen(input);
    if (ft_strnstr(input, "||", len) != NULL)
        return (1);
    if (ft_strnstr(input, "<<<", len) != NULL)
        return (1);
    if (ft_strnstr(input, ">>>", len) != NULL)
        return (1);
    return (0);
}

int ft_check_wrong_quotes(char *input)
{
    char **split_pipe;
    int i;
    int j;
    int count1;
    int count2;

    split_pipe = ft_split(input, '|');
    i = 0;
    count1 = 0;
    count2 = 0;
    while (split_pipe[i])
    {
        j = 0;
        while (split_pipe[i][j])
        {
            if (split_pipe[i][j] == '\'')
                count1++;
            if (split_pipe[i][j] == '\"')
                count2++;
            j++;
        }
        if (count1 % 2 == 1 || count2 % 2 == 1)
            return (1);
        i++;
    }
    i = 0;
    while (split_pipe[i])
    {
        free(split_pipe[i]);
        i++;
    }
    free(split_pipe);
    return (0);
}

int ft_check(char *input)
{
    if (ft_check_wrong_operator(input) == 1)
        return (1);
    if (ft_check_wrong_quotes(input) == 1)
        return (2);
    return (0);
}

