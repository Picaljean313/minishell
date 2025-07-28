/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanbis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:48:43 by anony             #+#    #+#             */
/*   Updated: 2025/07/28 14:04:18 by anony            ###   ########.fr       */
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

void	ft_free_command_redirin(t_command *command)
{
	t_redir	*redir;
	t_redir	*next;

	if (!command->redirin)
		return ;
	redir = command->redirin;
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
	command->redirin = NULL;
	return ;
}

void	ft_free_command_redirout(t_command *command)
{
	t_redir	*redir;
	t_redir	*next;

	if (!command->redirout)
		return ;
	redir = command->redirout;
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
	command->redirout = NULL;
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
		if (com->redirin)
			ft_free_command_redirin(com);
		if (com->redirout)
			ft_free_command_redirout(com);
		free(com);
		com = next;
	}
	shell->commands = NULL;
}
