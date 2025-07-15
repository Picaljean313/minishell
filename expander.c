/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:40:12 by anony             #+#    #+#             */
/*   Updated: 2025/07/15 20:18:53 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int ft_replace_var()
// {
    
// }


// char **ft_split_token(char *value)
// {
//     char **splittoken;
//     char *lastword;
//     int i;
//     int last;

//     if (!ft_strchr(value, '$'))
//         return;
//     splittoken = ft_split(value, '$');
//     if (value[(int)ft_strlen(value) - 1] == '$')
//     {
//         printf("hi\n");
//         last = 0;
//         while (splittoken[last])
//             last++;
//         lastword = malloc (((int)ft_strlen(splittoken[last - 1]) + 2) * sizeof(char));
//         i = 0;
//         while (splittoken[last - 1][i])
//         {
//             lastword[i] = splittoken[last - 1][i];
//             i++;
//         }
//         lastword[i] = '$';
//         lastword[i + 1] = '\0';
//         free(splittoken[last - 1]);
//         splittoken[last - 1] = lastword;
//     }
//     i = 0;
//     while (splittoken[i])
//     {
//         printf("word :-%s-\n", splittoken[i]);
//         i++;
//     }
//     return (splittoken);
// }

// char *ft_expand_token(char **tab, char *value)
// {
//     int firstexpand;
    
//     if (value[0] != '$')
//         firstexpand = 0;
//     else
//         firstexpand = 1;
// }

// int ft_check_expand_token(char *value)
// {
//     int i;

//     i = 0;
//     while (value[i])
//     {
//         if (value[i] == '$' && value[i + 1] == '$')
//             return (1);
//         i++;
//     }
//     return (0);
// }

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


// char *ft_replace_vars(char *token)
// {
//     int i;
//     int len;
//     int start;
//     int end;
//     int startvar;
//     int endvar;
//     int newlen;
//     char *newtoken;

//     char **tokensplit;

//     tokensplit

//     i = 0;
//     len = (int)ft_strlen(token);
//     newtoken = ft_strdup("");
//     newlen = 0;
//     while (i < len)
//     {
//         start = i;
//         end = i - 1;
//         if (token[i] != '$' || (token[i] == '$' && ft_is_simple_quote_active(token, i) == 1))
//         {
//             i++;
//             end++;
//         }
//         else
//         {
//             if (end - start >= 0)
//             {
//                 newtoken = ft_strjoin(newtoken, ft_truncate(token, start, end));
//             }

            
//             i++;
//             start = i;
//             while (token[i] != '\0' && token[i] != '\'' && token[i] != '\"' && token[i] != '$')
//                 i++;
//             end = i - 1;
//             ft_handle_var()
//         }
//     }
// }

char *ft_get_var_value(char **adress, int start, int end)
{
    char *value;
    char *var;
    char *varvalue;
    int i;
    
    value = *adress;
    printf("value :-%s-, start :-%d-, end :-%d-\n", value, start, end);
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
    printf("var:-%s-\n", var);
    if (!getenv(var))
        varvalue = ft_strdup("");
    else
        varvalue = ft_strdup(getenv(var));
    printf("varvalue:-%s-\n", varvalue);
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
        value = *adress;
        if (value[i] != '$' || (value[i] == '$' && ft_is_simple_quote_active(value, i) == 1))
            i++;
        else
        {
            if (!value[i + 1])
                break;
            printf("--hi--\n");
            start = i;
            end = i;
            i++;
            if (ft_isalpha(value[i]) == 1 || value[i] == '_')
            {
                i++;
                while (value[i] == '_' || ft_isalnum(value[i]) == 1)
                    i++;
            }   
            end = i - 1;
            printf("value :-%s-, start :-%d-, end :-%d-\n", value, start, end);
            if (ft_handle_var(adress, &start, &end) != 0)
                return (1);
            
        }
        printf("i:-%d-\n", i);
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
        printf("token:-%s-\n", token->value);
        token = token->next;
    }
    return (0);
}