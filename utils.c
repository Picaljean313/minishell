/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:01:34 by anony             #+#    #+#             */
/*   Updated: 2025/07/18 12:45:42 by anony            ###   ########.fr       */
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
