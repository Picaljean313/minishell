/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:12:40 by anony             #+#    #+#             */
/*   Updated: 2025/07/08 16:18:34 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void ft_set_shlvl(char **env)
{
    int i;
    int lvl;
    char *new_lvl;

    i = 0;
    while (env[i])
    {
        if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
        {
            lvl = ft_atoi(env[i] + 6) + 1;
            free(env[i]);
            new_lvl = ft_itoa(lvl);
            env[i] = ft_strjoin("SHLVL=", new_lvl);
            free(new_lvl);
            return ;
        }
        i++;
    }
    return ;
}

char **ft_set_env(char **env)
{
    int i;
    int j;
    char **env_copy;

    i = 0;
    while (env[i])
        i++;
    env_copy = malloc ((i + 1) * sizeof(char *));
    if (!env_copy)
        return (NULL);
    j = 0;
    while (j < i)
    {
        env_copy[j] = ft_strdup(env[j]);
        if (!env_copy[j])
        {
            while (j > 0)
            {
                free(env_copy[j - 1]);
                j--;
            }
            free(env_copy);
            return (NULL);
        }
        j++;
    }
    env_copy[j] = NULL;
    ft_set_shlvl(env_copy);
    return (env_copy);
}
