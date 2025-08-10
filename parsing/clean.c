/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:58:06 by anony             #+#    #+#             */
/*   Updated: 2025/08/10 19:36:48 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_env(t_shell *shell)
{
	int	i;

	if (!shell->env)
		return ;
	i = 0;
	while (shell->env[i])
	{
		free(shell->env[i]);
		shell->env[i] = NULL;
		i++;
	}
	free(shell->env);
	shell->env = NULL;
	return ;
}

void	ft_free_input(t_shell *shell)
{
	if (!shell->input)
		return ;
	free(shell->input);
	shell->input = NULL;
	return ;
}

void	ft_free_tokens(t_shell *shell)
{
	t_token	*token;
	t_token	*temp;

	if (!shell->tokens)
		return ;
	token = shell->tokens;
	while (token)
	{
		temp = token;
		token = token->next;
		if (temp->value)
		{
			free(temp->value);
			temp->value = NULL;
		}
		free(temp);
		temp = NULL;
	}
	shell->tokens = NULL;
	return ;
}

void	ft_clean_line(t_shell *shell)
{
	ft_free_input(shell);
	ft_free_tokens(shell);
	ft_free_commands(shell);
}

void	ft_clean_shell(t_shell *shell)
{
	ft_close_heredoc(shell);
	ft_free_env(shell);
	ft_free_input(shell);
	ft_free_tokens(shell);
	ft_free_commands(shell);
}
