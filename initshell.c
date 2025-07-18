/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:58:06 by anony             #+#    #+#             */
/*   Updated: 2025/07/18 13:19:18 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_check_params(int argc, char **argv, char **env)
{
	if (argc != 1 || !argv || !env)
		return (1);
    return (0);
}

int	ft_init_shell(t_shell *shell, char **envp)
{
	shell->env = ft_set_env(envp);
	if (!shell->env)
		return (1);
	shell->input = NULL;
	shell->exitcode = 0;
	shell->tokens = NULL;
	shell->pipes = NULL;
	return (0);
}

