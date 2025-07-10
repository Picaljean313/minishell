/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:44:51 by anony             #+#    #+#             */
/*   Updated: 2025/07/10 14:43:49 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// Faire check seulement hors quotes :
// int ft_check_wrong_operator(char *input)
// {
//     size_t len;

//     len = ft_strlen(input);
//     if (ft_strnstr(input, "||", len) != NULL)
//         return (1);
//     if (ft_strnstr(input, "<<<", len) != NULL)
//         return (1);
//     if (ft_strnstr(input, ">>>", len) != NULL)
//         return (1);
//     return (0);
// }

// PAS VIABLE :
// int ft_check_wrong_quotes(char *input)
// {
//     char **split_pipe;
//     int i;
//     int j;
//     int count1;
//     int count2;

//     split_pipe = ft_split(input, '|');
//     i = 0;
//     count1 = 0;
//     count2 = 0;
//     while (split_pipe[i])
//     {
//         j = 0;
//         while (split_pipe[i][j])
//         {
//             if (split_pipe[i][j] == '\'')
//                 count1++;
//             if (split_pipe[i][j] == '\"')
//                 count2++;
//             j++;
//         }
//         if (count1 % 2 == 1 || count2 % 2 == 1)
//             return (1);
//         i++;
//     }
//     i = 0;
//     while (split_pipe[i])
//     {
//         free(split_pipe[i]);
//         i++;
//     }
//     free(split_pipe);
//     return (0);
// }

int ft_check_wrong_operator(char *input, int ind)
{
    if (input[ind] == '|')
        if (input[ind + 1])
            if (input[ind + 1] == '|')
                return (1);
    if (input[ind] == '<')
        if (input[ind + 1])
            if (input[ind + 1] == '<')
                if (input[ind + 2])
                    if (input[ind + 2] == '<')
                        return (1);
    if (input[ind] == '>')
        if (input[ind + 1])
            if (input[ind + 1] == '>')
                if (input[ind + 2])
                    if (input[ind + 2] == '>')
                        return (1);
    return (0);
}

int ft_check(char *input)
{
    int i;
    int sq;
    int dq;
    char last; 
    
    i = 0;
    sq = 0;
    dq = 0;
    last = '\0';
    while (input[i])
    {
        if (sq == 0 && dq == 0)
            if (ft_check_wrong_operator(input, i) != 0)
                return (1);
        if (input[i] == '\'')
        {
            if (sq == 0 && dq == 0)
                sq = 1;
            else if (sq == 1 && dq == 0)
                sq = 0;
            else if (sq == 0 && dq == 1)
            {
                sq = 1;
                last = '\'';
            }
            else if (sq == 1 && dq == 1 && last == '\'')
            {
                sq = 0;
                last = '\0';
            }
            else if (sq == 1 && dq == 1 && last == '\"')
            {
                sq = 0;
                dq = 0;
                last = '\0';
            }
        }
        if (input[i] == '\"')
        {
            if (sq == 0 && dq == 0)
                dq = 1;
            else if (sq == 1 && dq == 0)
            {
                dq = 1;
                last = '\"';
            }
            else if (sq == 0 && dq == 1)
                dq = 0;
            else if (sq == 1 && dq == 1 && last == '\"')
            {
                dq = 0;
                last = '\0';
            }
            else if (sq == 1 && dq == 1 && last == '\'')
            {
                sq = 0;
                dq = 0;
                last = '\0';
            }
        }
        i++;
    }
    if (sq != 0 || dq != 0)
        return (2);
    return (0);
}

int ft_is_quote_active(char *input, int ind)
{
    int i;
    int sq;
    int dq;
    char last; 
    
    if (ind >= (int)ft_strlen(input))
        return (2);
    i = 0;
    sq = 0;
    dq = 0;
    last = '\0';
    while (i < ind)
    {
        if (input[i] == '\'')
        {
            if (sq == 0 && dq == 0)
                sq = 1;
            else if (sq == 1 && dq == 0)
                sq = 0;
            else if (sq == 0 && dq == 1)
            {
                sq = 1;
                last = '\'';
            }
            else if (sq == 1 && dq == 1 && last == '\'')
            {
                sq = 0;
                last = '\0';
            }
            else if (sq == 1 && dq == 1 && last == '\"')
            {
                sq = 0;
                dq = 0;
                last = '\0';
            }
        }
        if (input[i] == '\"')
        {
            if (sq == 0 && dq == 0)
                dq = 1;
            else if (sq == 1 && dq == 0)
            {
                dq = 1;
                last = '\"';
            }
            else if (sq == 0 && dq == 1)
                dq = 0;
            else if (sq == 1 && dq == 1 && last == '\"')
            {
                dq = 0;
                last = '\0';
            }
            else if (sq == 1 && dq == 1 && last == '\'')
            {
                sq = 0;
                dq = 0;
                last = '\0';
            }
        }
        i++;
    }
    if (sq != 0 || dq != 0)
        return (1);
    return (0);
}

char *ft_truncate(char *str, int start, int end)
{
    char *strtrunc;
    int i;
    
    if (start < 0 || start > end || end > (int)ft_strlen(str) - 1)
        return NULL;
    strtrunc = malloc ((end - start + 2) * sizeof(char));
    if (strtrunc == NULL)
        return NULL;
    i = 0;
    while (start <= end)
    {
        strtrunc[i] = str[start];
        start++;
        i++;
    }
    strtrunc[i] = '\0';
    return (strtrunc);
}

char *ft_next_token_value(char *input, int *ind)
{
    int start;
    int end;
    int quotes;
    char *tokenvalue;
    int i;

    i = *ind;
    if (i >= (int)ft_strlen(input))
        return NULL;
    
    while (input[i] == ' ')
        i++;
    start = i;
    if (input[i] == '|')
    {
        tokenvalue = "|";
        i++;
        *ind = i;
        // printf("token : %s\n", tokenvalue);
        // printf("i : %d\n", i);
        return (tokenvalue);
    }
    if (input[i] == '<')
    {
        if (input[i + 1] == '<')
        {
            tokenvalue = "<<";
            i += 2;
            *ind = i;
            // printf("token : %s\n", tokenvalue);
            // printf("i : %d\n", i);
            return (tokenvalue);
        }
        tokenvalue = "<";
        i++;
        *ind = i;
        // printf("token : %s\n", tokenvalue);
        // printf("i : %d\n", i);
        return (tokenvalue);
    }
    if (input[i] == '>')
    {
        if (input[i + 1] == '>')
        {
            tokenvalue = ">>";
            i += 2;
            *ind = i;
            // printf("token : %s\n", tokenvalue);
            // printf("i : %d\n", i);
            return (tokenvalue);
        }
        tokenvalue = ">";
        i++;
        *ind = i;
        // printf("token : %s\n", tokenvalue);
        // printf("i : %d\n", i);
        return (tokenvalue);
    }
        
    while (input[i])
    {
        quotes = ft_is_quote_active(input, i);
        if (quotes == 0 && (input[i] == '|' || input[i] == '<' || input[i] == '>' || input[i] == ' '))
            break ;
        i++;
    }
    end = i - 1;
    if (end < start)
        return NULL;
    *ind = i;
    tokenvalue = ft_truncate(input, start, end);
    // printf("token : %s\n", tokenvalue);
    // printf("i : %d\n", i);
    return (tokenvalue);
}

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

t_token_type ft_get_token_type(char *value)
{
    if (ft_strncmp(value, "|", 1) == 0)
        return (PIPE);
    if (ft_strncmp(value, "<<", 2) == 0)
        return (HEREDOC);
    if (ft_strncmp(value, ">>", 2) == 0)
        return (APPEND);
    if (ft_strncmp(value, "<", 1) == 0)
        return (REDIR_IN);
    if (ft_strncmp(value, ">", 1) == 0)
        return (REDIR_OUT);
    else
        return (WORD);
}

t_token **ft_lexer(char *input)
{
    t_token **tokentab;
    char *value;
    t_token_type tokentype;
    int ind;

    tokentab = malloc (sizeof(t_token **));
    *tokentab = NULL;
    ind = 0;
    while (ind < (int)ft_strlen(input))
    {
        value = ft_next_token_value(input, &ind);
        tokentype = ft_get_token_type(value);
        ft_add_token(tokentab, tokentype, value);
    }
    return (tokentab);
}

void ft_show_tokentab(t_token **tab)
{
    t_token *token;

    token = *tab;
    while (token)
    {
        printf("enum : %d\n", token->type);
        printf("value : %s\n", token->value);
        token = token->next;
    }
    return ;
}


// int ft_check(char *input)
// {
//     // if (ft_check_wrong_operator(input) == 1)
//     //     return (1);
//     if (ft_check_quotes(input) == 1)
//         return (2);
//     return (0);
//}



/*
regles :
espaces ignores sauf si dans quotes
si plusieurs espaces entre deux words, un seul pris en compte (ex : echo hihi    haha -> hihi haha)
$ affiche que si fin de sequence de caracteres (avec un espace apres)
*/