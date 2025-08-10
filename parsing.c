/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:36:32 by anony             #+#    #+#             */
/*   Updated: 2025/08/10 19:20:45 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parsing(t_shell *shell)
{
	shell->input = readline("minishell_oh_yeah$ ");
	if (!shell->input)
		return (2);
	if (ft_check_input(shell->input) != 0)
		return (g_signal = 2, ft_putstr_fd("Bad input\n", STDERR_FILENO), 1);
	if (ft_lexer(shell) != 0)
		return (g_signal = 1, ft_putstr_fd("Lexer fail\n", STDERR_FILENO), 2);
	if (ft_expand(shell) != 0)
		return (g_signal = 1, ft_putstr_fd("Expand fail\n", STDERR_FILENO), 2);
	if (ft_check_commands(shell) != 0)
		return (g_signal = 2, ft_putstr_fd("Bad command\n", STDERR_FILENO), 1);
	if (ft_parser(shell) != 0)
		return (g_signal = 1, ft_putstr_fd("Parser fail\n", STDERR_FILENO), 2);
	if (ft_handle_heredocs(shell) != 0)
		return (1);
	add_history(shell->input);
	return (0);
}
