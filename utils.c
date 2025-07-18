/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:01:34 by anony             #+#    #+#             */
/*   Updated: 2025/07/18 17:40:36 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_getenv(char *var, char **env)
{
    int i;
    int len;
    char *value;

    i = 0;
    len = ft_strlen(var);
    while (env[i])
    {
        if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
        {
            value = ft_strdup(env[i] + len + 1);
            return (value);
        }
        i++;
    }
    return (NULL);
}

int ft_is_quote_active(char *input, int ind)
{
    int i;
    int sq;
    int dq;
    int last; 
    
    if (ind >= (int)ft_strlen(input))
        return (2);
    i = 0;
    sq = 0;
    dq = 0;
    last = '\0';
    while (i < ind)
    {
        if (input[i] == '\'')
            ft_handle_simple_quote(&sq, &dq, &last);
        if (input[i] == '\"')
            ft_handle_double_quote(&sq, &dq, &last);
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
    
    if (!str || start < 0 || start > end || end > (int)ft_strlen(str) - 1)
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