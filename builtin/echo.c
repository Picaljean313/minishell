/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:02:19 by anony             #+#    #+#             */
/*   Updated: 2025/07/30 19:41:06 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_tab_len(char **tab)
{
    int len;

    len = 0;
    while (tab[len])
        len++;
    return (len);
}

int ft_echo(t_command *command)
{
    int i;
    
    if (!command->args || ft_strncmp(command->args[0], "echo", 5) != 0)
        return (1);
    if (!command->args[1])
        return (printf("\n"), 0);
    if (ft_strncmp(command->args[1], "-n", 3) == 0)
        i = 2;
    else
        i = 1;
    while (i < ft_tab_len(command->args) - 1)
    {
        printf("%s ", command->args[i]);
        i++;
    }
    if (command->args[i])
    {
        if (ft_strncmp(command->args[1], "-n", 3) == 0)
            printf("%s", command->args[i]);
        else
            printf("%s\n", command->args[i]);
    }
    return (0);
}
