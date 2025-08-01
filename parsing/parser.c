/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:20:00 by anony             #+#    #+#             */
/*   Updated: 2025/08/01 20:17:46 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_init_command(t_command *command)
{
	if (!command)
		return (1);
	command->args = NULL;
	command->redir = NULL;
	command->pid = -1;
	command->fdin = STDIN_FILENO;
	command->fdout = STDOUT_FILENO;
	command->next = NULL;
	return (0);
}

int	ft_fill_command_bis(t_token *token, t_command *command)
{
	while (token->type != PIPE)
	{
		if (token->type == WORD)
		{
			if (ft_add_arg(token, command) != 0)
				return (1);
		}
		else
		{
			if (ft_add_redir(token, command) != 0)
				return (1);
			token = token->next;
		}
		token = token->next;
		if (!token)
			break ;
	}
	return (0);
}

int	ft_fill_command(t_command *com, t_token *token, t_shell *shell)
{
	t_command	*tmp;

	if (!shell->commands)
		shell->commands = com;
	else
	{
		tmp = shell->commands;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = com;
	}
	if (ft_fill_command_bis(token, com) != 0)
		return (1);
	return (0);
}

int	ft_parser(t_shell *shell)
{
	t_command	*command;
	t_token		*token;

	token = shell->tokens;
	if (!token)
		return (1);
	while (token)
	{
		command = malloc(sizeof(t_command));
		if (!command)
			return (1);
		if (ft_init_command(command) != 0)
			return (1);
		ft_fill_command(command, token, shell);
		while (token->next && token->type != PIPE)
			token = token->next;
		token = token->next;
	}
	return (0);
}
