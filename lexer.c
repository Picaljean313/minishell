/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:41:36 by anony             #+#    #+#             */
/*   Updated: 2025/07/18 17:54:37 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_next_token_value(char *input, int *ind)
{
    char *tokenvalue;

    tokenvalue = NULL;
    if (!input || *ind > (int)ft_strlen(input)
            || ft_is_quote_active(input, *ind) == 1)
        return (NULL);
    while (input[*ind] == ' ' || (input[*ind] >= 9 && input[*ind] <= 13))
        (*ind)++;
    if (!input[*ind])
        return (ft_strdup(""));
    if (input[*ind] == '|' || input[*ind] == '<' || input[*ind] == '>')
    {
        if (ft_handle_no_word_token(input, ind, &tokenvalue) != 0)
            return (NULL);
    }
    else
    {
        if (ft_handle_word_token(input, ind, &tokenvalue) != 0)
            return (NULL);
    }
    return (tokenvalue);
}

t_token_type ft_get_token_type(char *value)
{
    if (ft_strncmp(value, "|", 1) == 0)
        return (PIPE);
    if (ft_strncmp(value, "<<", 2) == 0)
        return (REDIR_HEREDOC);
    if (ft_strncmp(value, ">>", 2) == 0)
        return (REDIR_APPEND);
    if (ft_strncmp(value, "<", 1) == 0)
        return (REDIR_IN);
    if (ft_strncmp(value, ">", 1) == 0)
        return (REDIR_OUT);
    else
        return (WORD);
}

int ft_add_token(t_token **tab, t_token_type type, char *value)
{
    t_token *token;
    t_token *temp;

    if (!tab || !value)
        return (1);
    token = malloc(sizeof(t_token));
    if (!token)
        return (1);
    token->type = type;
    token->value = ft_strdup(value);
    if (!token->value)
        return (1);
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
    return (0);
}

t_token **ft_lexer(char *input)
{
    t_token **tokentab;
    char *value;
    t_token_type tokentype;
    int ind;

    if (!input)
        return (NULL);
    tokentab = malloc (sizeof(t_token **));
    if (!tokentab)
        return (NULL);
    *tokentab = NULL;
    ind = 0;
    while (ind < (int)ft_strlen(input))
    {
        value = ft_next_token_value(input, &ind);
        if (!value)
            return (NULL);
        if (ft_strncmp("", value, 1) == 0)
            break ;
        tokentype = ft_get_token_type(value);
        if (ft_add_token(tokentab, tokentype, value) != 0)
            return (NULL);
    }
    return (tokentab);
}
