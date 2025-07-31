/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:06:08 by anony             #+#    #+#             */
/*   Updated: 2025/07/31 16:20:19 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_env(t_command *command, t_shell *shell)
{
    int	i;

    if (!command->args || ft_strncmp(command->args[0], "env", 4) != 0)
		return (1);
	if (command->args[1])
		return (0);
	i = 0;
	if (!shell->env)
		return (0);
	while (shell->env[i])
	{
        if (ft_strchr(shell->env[i], '='))
		    printf("%s\n", shell->env[i]);
		i++;
	}
    return (0);
}