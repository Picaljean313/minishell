/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:40:12 by anony             #+#    #+#             */
/*   Updated: 2025/07/16 17:19:54 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int ft_is_simple_quote_active(char *value, int ind)
{
    int i;
    int sq;
    int dq;
    char last; 
    
    if (ind >= (int)ft_strlen(value))
        return (2);
    i = 0;
    sq = 0;
    dq = 0;
    last = '\0';
    while (i < ind)
    {
        if (value[i] == '\'')
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
        if (value[i] == '\"')
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
    if ((sq != 0 && dq == 0) || (sq != 0 && dq != 0 && last == '\"'))
        return (1);
    return (0);
}

char *ft_get_var_value(char **adress, int start, int end)
{
    char *value;
    char *var;
    char *varvalue;
    int i;
    
    value = *adress;
    if (end - start == 0)
        var = ft_strdup("");
    else
    {
        var = malloc((end - start + 1) * sizeof(char));
        i = 0;
        while(value[start + 1 + i] && start + 1 + i <= end)
        {
            var[i] = value[start + 1 + i];
            i++;
        }
        var[i] = '\0';
    }
    if (!getenv(var))
        varvalue = ft_strdup("");
    else
        varvalue = ft_strdup(getenv(var));
    free(var);
    return (varvalue);
}

int ft_handle_var(char **adress, int *start, int *end)
{
    char *value;
    char *varvalue;
    char *newvalue;
    int newlen;
    int i;
    int j;
    int offset;

    value = *adress;
    varvalue = ft_get_var_value(adress, *start, *end);
    offset = (int)ft_strlen(varvalue) - (*end - *start + 1);
    newlen = (int)ft_strlen(value) + offset;
    newvalue = malloc ((newlen + 1) * sizeof(char));
    i = 0;
    j = 0;
    while (i < *start)
    {
        newvalue[i] = value[i];
        i++;
    }
    while (varvalue[j])
    {
        newvalue[i] = varvalue[j];
        i++;
        j++;
    }
    j = *end + 1;
    while (value[j])
    {
        newvalue[i] = value[j];
        i++;
        j++;
    }
    newvalue[i] = '\0';
    free(*adress);
    *adress = newvalue;
    *start += offset;
    *end += offset;
    return (0);
}

int ft_handle_var_exit_status(char **adress, int *start, int *end)
{
    char *value;
    char *varvalue;
    char *newvalue;
    int newlen;
    int i;
    int j;
    int offset;

    value = *adress;
    printf("%d\n", g_exitstatus);
    varvalue = ft_itoa(g_exitstatus);
    offset = (int)ft_strlen(varvalue) - (*end - *start + 1);
    newlen = (int)ft_strlen(value) + offset;
    newvalue = malloc ((newlen + 1) * sizeof(char));
    i = 0;
    j = 0;
    while (i < *start)
    {
        newvalue[i] = value[i];
        i++;
    }
    while (varvalue[j])
    {
        newvalue[i] = varvalue[j];
        i++;
        j++;
    }
    j = *end + 1;
    while (value[j])
    {
        newvalue[i] = value[j];
        i++;
        j++;
    }
    newvalue[i] = '\0';
    free(*adress);
    *adress = newvalue;
    *start += offset;
    *end += offset;
    return (0);
}

int ft_replace_vars(char **adress)
{
    int i;
    char *value;
    int start;
    int end;


    i = 0;
    value = *adress;
    while (i < (int)ft_strlen(value))
    {
        if (value[i] != '$' || (value[i] == '$' && ft_is_simple_quote_active(value, i) == 1))
            i++;
        else
        {
            if (!value[i + 1])
                break;
            start = i;
            end = i;
            i++;
            if (value[i] == '?')
            {
                i++;
                end = i - 1;
                if (ft_handle_var_exit_status(adress, &start, &end) != 0)
                    return (1);
                value = *adress;
                continue ;
            }
            if (ft_isalpha(value[i]) == 1 || value[i] == '_')
            {
                i++;
                while (value[i] == '_' || ft_isalnum(value[i]) == 1)
                    i++;
            }   
            end = i - 1;
            if (ft_handle_var(adress, &start, &end) != 0)
                return (1);
            value = *adress;
        }
    }
    return (0);
}

int ft_handle_quote(char **valueadress, int start, int end)
{
    char *value;
    char *newvalue;
    int newlen;
    int i;

    value = *valueadress;
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
    *valueadress = newvalue;
    return (0);
}

int ft_remove_quotes(char **valueadress)
{
    char *value;
    int start;
    int end;
    char quote;

    value = *valueadress;
    start = 0;
    while (value[start])
    {
        if (value[start] == '\"' || value[start] == '\'')
        {
            if (value[start] == '\"')
                quote = '\"';
            else
                quote = '\'';
            end = start;
            end++;
            while (value[end] && value[end] != quote)
                end++;
            if (!value[end])
                return (1);
            if (ft_handle_quote(valueadress, start, end) != 0)
                return (1);
            value = *valueadress;
            start = end - 1;
        }
        else
            start++;
    }
    return (0);
}

int ft_expand(t_token **tokentab)
{
    t_token *token;

    if (!*tokentab)
        return (1);
    token = *tokentab;
    while (token)
    {
        // if (ft_check_expand_token(token->value) != 0)
        //     return (1);
        // ft_expand_token(token->value);
        if (ft_replace_vars(&token->value) != 0)
            return (1);
        if (ft_remove_quotes(&token->value) != 0)
            return (1);
        printf("token:-%s-\n", token->value);
        token = token->next;
    }
    return (0);
}