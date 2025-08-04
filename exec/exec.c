/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:27:16 by anony             #+#    #+#             */
/*   Updated: 2025/08/04 22:37:46 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_exec_simple_builtin(t_command *command, t_shell *shell)
{
	t_redir *redir;
	int savedfdout;
	int savedfdin;

	savedfdin =  dup(STDIN_FILENO);
	savedfdout = dup(STDOUT_FILENO);
	redir = command->redir;
	if (ft_redir(redir) != 0)
	{
		dup2(savedfdin, STDIN_FILENO);
		ft_close_fd(&savedfdin);
		dup2(savedfdout, STDOUT_FILENO);
		ft_close_fd(&savedfdout);
		return (0);
	}
	if (ft_exec_builtin (command, shell) != 0)
	{
		dup2(savedfdin, STDIN_FILENO);
		ft_close_fd(&savedfdin);
		dup2(savedfdout, STDOUT_FILENO);
        ft_close_fd(&savedfdout);
		return (1);
	}
	dup2(savedfdin, STDIN_FILENO);
    ft_close_fd(&savedfdin);
	dup2(savedfdout, STDOUT_FILENO);
    ft_close_fd(&savedfdout);
	return(0);
}


int ft_exec (t_shell *shell)
{
    
    // si cest un builtin seul
	if (!shell->commands)
		return (1);
	if (!shell->commands->next && ft_is_builtin(shell->commands) == 0)
	{
		if (ft_exec_simple_builtin(shell->commands, shell) != 0)
			return (1);
		g_signal = 0;
		return (0);
	}

	return (0);
}

