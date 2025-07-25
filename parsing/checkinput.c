/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkinput.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:45:41 by anony             #+#    #+#             */
/*   Updated: 2025/07/25 17:57:47 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_wrong_operator(char *input, int ind)
{
	if (input[ind] == '|')
		if (input[ind + 1])
			if (input[ind + 1] == '|')
				return (1);
	if (input[ind] == '<')
		if (input[ind + 1])
			if (input[ind + 1] == '<')
				if (input[ind + 2])
					if (input[ind + 2] == '<')
						return (1);
	if (input[ind] == '>')
		if (input[ind + 1])
			if (input[ind + 1] == '>')
				if (input[ind + 2])
					if (input[ind + 2] == '>')
						return (1);
	return (0);
}

int	ft_check_input(char *input)
{
	int	i;
	int	sq;
	int	dq;
	int	last;

	i = 0;
	sq = 0;
	dq = 0;
	last = 0;
	if (!input[0])
		return (1);
	while (input[i])
	{
		if (sq == 0 && dq == 0)
			if (ft_check_wrong_operator(input, i) != 0)
				return (1);
		if (input[i] == '\'')
			ft_handle_simple_quote(&sq, &dq, &last);
		if (input[i] == '\"')
			ft_handle_double_quote(&sq, &dq, &last);
		i++;
	}
	if (sq != 0 || dq != 0)
		return (1);
	return (0);
}
