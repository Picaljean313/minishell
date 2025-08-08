/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:23:38 by anony             #+#    #+#             */
/*   Updated: 2025/08/08 11:19:02 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_not_only_spaces(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (!(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
			return (0);
		i++;
	}
	return (1);
}

void	ft_remove_first_empty_tokens(t_shell *shell)
{
	t_token	*temp;

	if (!shell->tokens)
		return ;
	while (ft_strncmp(shell->tokens->value, "", 1) == 0
		|| ft_not_only_spaces(shell->tokens->value) != 0)
	{
		temp = shell->tokens;
		shell->tokens = shell->tokens->next;
		free(temp->value);
		free(temp);
		if (!shell->tokens)
			return ;
	}
}

void	ft_remove_empty_tokens(t_shell *shell)
{
	t_token	*token;
	t_token	*temp;

	ft_remove_first_empty_tokens(shell);
	token = shell->tokens;
	while (token)
	{
		temp = token->next;
		if (!temp)
			return ;
		if ((ft_strncmp(temp->value, "", 1) == 0
			|| ft_not_only_spaces(temp->value) != 0)
			&& token->type != REDIR_HEREDOC)
		{
			token->next = temp->next;
			free(temp->value);
			free(temp);
		}
		else
			token = token->next;
	}
}

int	ft_expand(t_shell *shell)
{
	t_token	*token;

	if (!shell->tokens)
		return (1);
	token = shell->tokens;
	while (token)
	{
		if (!token->value)
			return (1);
		if (token->type == REDIR_HEREDOC)
		{
			token = token->next;
			if (ft_remove_quotes(&token->value) != 0)
				return (1);
		}
		else
		{
			if (ft_replace_vars(&token->value, shell) != 0)
				return (1);
			if (ft_remove_quotes(&token->value) != 0)
				return (1);
		}
		token = token->next;
	}
	return (ft_remove_empty_tokens(shell), 0);
}
