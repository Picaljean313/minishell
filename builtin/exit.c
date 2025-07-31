/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:06:16 by anony             #+#    #+#             */
/*   Updated: 2025/07/31 15:39:12 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_is_numeric(char *value)
{
    int i;

    i = 0;
	while (value[i] == ' ' || (value[i] >= '\t' && value[i] <= '\r'))
        i++;
    if (ft_isdigit(value[i]) != 1)
        return (1);
    while (ft_isdigit(value[i]) == 1)
        i++;
    while (value[i] == ' ' || (value[i] >= '\t' && value[i] <= '\r'))
        i++;
    if (value[i])
        return (1);
    return (0);
}

int ft_exit(t_command *command)
{
    int code;

    if (!command->args || ft_strncmp(command->args[0], "exit", 5) != 0)
        return (1);
    if (!command->args[1])
        exit(0);
    if (ft_is_numeric(command->args[1]) != 0)
        exit(255);
    if (command->args[2])
    {
        printf("exit: too many arguments\n");
        return (0);
    }
    code = ft_atoi(command->args[1]) % 256;
    exit(code);
    return (0);
}
