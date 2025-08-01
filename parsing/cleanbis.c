/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanbis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:48:43 by anony             #+#    #+#             */
/*   Updated: 2025/08/01 13:44:44 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_command_args(t_command *command)
{
	int	i;

	i = 0;
	if (!command->args)
		return ;
	while (command->args[i])
	{
		free(command->args[i]);
		command->args[i] = NULL;
		i++;
	}
	free(command->args);
	command->args = NULL;
}

void	ft_free_command_redir(t_command *command)
{
	t_redir	*redir;
	t_redir	*next;

	if (!command->redir)
		return ;
	redir = command->redir;
	while (redir)
	{
		next = redir->next;
		if (redir->file)
		{
			free(redir->file);
			redir->file = NULL;
		}
		free(redir);
		redir = next;
	}
	command->redir = NULL;
	return ;
}

void	ft_free_commands(t_shell *shell)
{
	t_command	*com;
	t_command	*next;

	if (!shell->commands)
		return ;
	com = shell->commands;
	while (com)
	{
		next = com->next;
		if (com->args)
			ft_free_command_args(com);
		if (com->redir)
			ft_free_command_redir(com);
		free(com);
		com = next;
	}
	shell->commands = NULL;
}
