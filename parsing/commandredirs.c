/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandredirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:35:44 by anony             #+#    #+#             */
/*   Updated: 2025/08/06 17:58:20 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_add_redir(t_token *token, t_command *command)
{
	t_redir	*redir;
	t_redir	*tmp;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (1);
	redir->type = token->type;
	redir->file = ft_strdup(token->next->value);
	redir->heredocfd = -1;
	redir->next = NULL;
	if (!command->redir)
		command->redir = redir;
	else
	{
		tmp = command->redir;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
	return (0);
}
