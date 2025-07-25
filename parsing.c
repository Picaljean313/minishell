/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:36:32 by anony             #+#    #+#             */
/*   Updated: 2025/07/25 19:41:01 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parsing(t_shell *shell)
{
	shell->input = readline("minishell_oh_yeah$ ");
	if (!shell->input)
		return (2);
	add_history(shell->input);
	if (ft_check_input(shell->input) != 0)
		return (printf("Your input sucks\n"), 1);
	if (ft_lexer(shell) != 0)
		return (printf("Lexer failed\n"), 1);
	if (ft_expand(shell) != 0)
		return (printf("Expand failed\n"), 1);
	if (ft_check_commands(shell) != 0)
		return (printf("Your commands sucks\n"), 1);
	if (ft_parser(shell) != 0)
		return (printf("Parser failed\n"), 1);
	return (0);
}
