/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:59:46 by anony             #+#    #+#             */
/*   Updated: 2025/07/30 18:21:05 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_add_env_value(char *value, char **env)
{
    char **newenv;
    int	i;
    int len;

    if (!env)
        return (1);
    len = 0;
    while (env[len])
        len++;
    newenv = malloc ((len + 2) * sizeof(char *));
    if (!newenv)
        return (1);
    i = 0;
    while (i < len)
    {
        newenv[i] = env[i];
        i++;
    }
    newenv[i] = value;
    i++;
    newenv[i] = NULL;
    free(env);
    env = newenv;
    return (0);
}
