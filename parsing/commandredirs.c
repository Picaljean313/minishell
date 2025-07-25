/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandredirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:35:44 by anony             #+#    #+#             */
/*   Updated: 2025/07/25 18:14:31 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_redirin(t_redir *redir, t_token *token, t_command *command)
{
	t_redir	*tmp;

	redir->type = token->type;
	redir->file = ft_strdup(token->next->value);
	redir->next = NULL;
	if (!command->redirin)
		command->redirin = redir;
	else
	{
		tmp = command->redirin;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
}

void	ft_add_redirout(t_redir *redir, t_token *token, t_command *command)
{
	t_redir	*tmp;

	redir->type = token->type;
	redir->file = ft_strdup(token->next->value);
	redir->next = NULL;
	if (!command->redirout)
		command->redirout = redir;
	else
	{
		tmp = command->redirout;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
}

int	ft_add_redir(t_token *token, t_command *command)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (1);
	redir->file = NULL;
	redir->type = 0;
	redir->next = NULL;
	if (token->type == REDIR_IN || token->type == REDIR_HEREDOC)
		ft_add_redirin(redir, token, command);
	if (token->type == REDIR_OUT || token->type == REDIR_APPEND)
		ft_add_redirout(redir, token, command);
	return (0);
}
