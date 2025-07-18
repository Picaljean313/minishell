/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:54:29 by anony             #+#    #+#             */
/*   Updated: 2025/07/17 19:25:51 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_env(char ***env)
{
    int i;

    i = 0;
    while ((*env)[i])
    {
        free((*env)[i]);
        i++;
    }
    free(*env);
    return ;
}

void ft_clean_shell(t_shell *shell)
{
    ft_free_env(&shell->env);
    return ;
}