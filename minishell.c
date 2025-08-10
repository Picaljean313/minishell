/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:52:09 by anony             #+#    #+#             */
/*   Updated: 2025/08/10 19:18:06 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal;

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	int		res;

	g_signal = 0;
	if (ft_check_params(argc, argv, envp) != 0)
		return (1);
	if (ft_init_shell(&shell, envp) != 0)
		return (ft_clean_shell(&shell), 1);
	while (1)
	{
		ft_signal_handler(MAIN);
		res = ft_parsing(&shell);
		if (res == 2)
			return (ft_clean_shell(&shell), 2);
		if (res == 1)
		{
			ft_clean_line(&shell);
			continue ;
		}
		if (ft_exec(&shell) != 0)
			return (ft_clean_shell(&shell), 1);
		ft_clean_line(&shell);
	}
	rl_clear_history();
	return (ft_clean_shell(&shell), g_signal);
}
