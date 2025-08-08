/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkcommands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:36:25 by anony             #+#    #+#             */
/*   Updated: 2025/08/08 21:11:38 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_empty_command(t_token *token)
{
	if (!token)
		return (1);
	if (token->type == PIPE)
		return (1);
	while (token)
	{
		if (token->type == PIPE)
		{
			if (token->next)
			{
				token = token->next;
				if (token->type == PIPE)
					return (1);
			}
			else
				return (1);
		}
		token = token->next;
	}
	return (0);
}

int	ft_check_command(t_token *token)
{
	while (token->type != PIPE)
	{
		if (token->type != WORD)
		{
			token = token->next;
			if (!token)
				return (1);
			if (token->type != WORD)
				return (1);
		}
		token = token->next;
		if (!token)
			break ;
	}
	return (0);
}

int	ft_check_commands(t_shell *shell)
{
	t_token	*token;

	if (!shell->tokens)
		return (0);
	if (ft_check_empty_command(shell->tokens) != 0)
		return (1);
	token = shell->tokens;
	while (token)
	{
		if (ft_check_command(token) != 0)
			return (1);
		while (token->next && token->type != PIPE)
			token = token->next;
		token = token->next;
	}
	return (0);
}
