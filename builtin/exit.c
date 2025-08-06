/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:06:16 by anony             #+#    #+#             */
/*   Updated: 2025/08/06 19:34:05 by anony            ###   ########.fr       */
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

int ft_exit(t_command *command, t_shell *shell, t_savedfds *fds)
{
    int code;

    if (!command->args || ft_strncmp(command->args[0], "exit", 5) != 0)
        return (1);
    if (command->args[1] && command->args[2])
    {
        g_signal = 2;
        ft_putstr_fd("exit\n", STDOUT_FILENO);
        return (ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO), 0);
    }
    if (command->args[1] && ft_is_numeric(command->args[1]) != 0)
    {
        g_signal = 2;
        ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
    }
    if (command->args[1] && ft_is_numeric(command->args[1]) == 0)
    {
        code = ft_atoi(command->args[1]) % 256;
        g_signal = code;
    }
    ft_putstr_fd("exit\n", STDOUT_FILENO);
    if (ft_restore_savedfd(fds) != 0)
        return (1);
    ft_clean_shell(shell);
    exit(g_signal);
}
