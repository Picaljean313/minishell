/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:41:36 by anony             #+#    #+#             */
/*   Updated: 2025/07/25 19:32:38 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_next_token_value(char *input, int *ind)
{
	char	*tokenvalue;

	if (!input || *ind >= (int)ft_strlen(input)
		|| ft_is_quote_active(input, *ind) == 1)
		return (NULL);
	if (input[*ind] == '|' || input[*ind] == '<' || input[*ind] == '>')
	{
		if (ft_handle_no_word_token(input, ind, &tokenvalue) != 0)
			return (NULL);
	}
	else
	{
		if (ft_handle_word_token(input, ind, &tokenvalue) != 0)
			return (NULL);
	}
	while (input[*ind] == ' ' || (input[*ind] >= 9 && input[*ind] <= 13))
		(*ind)++;
	return (tokenvalue);
}

t_type	ft_get_token_type(char *value)
{
	if (ft_strncmp(value, "|", 1) == 0)
		return (PIPE);
	if (ft_strncmp(value, "<<", 2) == 0)
		return (REDIR_HEREDOC);
	if (ft_strncmp(value, ">>", 2) == 0)
		return (REDIR_APPEND);
	if (ft_strncmp(value, "<", 1) == 0)
		return (REDIR_IN);
	if (ft_strncmp(value, ">", 1) == 0)
		return (REDIR_OUT);
	else
		return (WORD);
}

int	ft_add_token(t_shell *shell, t_token *token)
{
	t_token	*temp;

	if (!token)
		return (1);
	if (!shell->tokens)
		shell->tokens = token;
	else
	{
		temp = shell->tokens;
		while (temp->next)
			temp = temp->next;
		temp->next = token;
	}
	return (0);
}

int	ft_lexer(t_shell *shell)
{
	t_token	*token;
	int		ind;

	ind = 0;
	while (ind < (int)ft_strlen(shell->input))
	{
		token = malloc(sizeof(t_token));
		if (!token)
			return (1);
		token->type = 0;
		token->next = NULL;
		token->value = ft_next_token_value(shell->input, &ind);
		if (!token->value)
			return (ft_free_token(token), 1);
		token->type = ft_get_token_type(token->value);
		if (ft_add_token(shell, token) != 0)
			return (ft_free_token(token), 1);
	}
	return (0);
}
