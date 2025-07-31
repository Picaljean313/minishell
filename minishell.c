/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:52:09 by anony             #+#    #+#             */
/*   Updated: 2025/07/31 15:39:01 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

void	ft_show(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
	{
		printf("no tab\n");
		return ;
	}
	printf("start\n");
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	printf("end\n");
}

void	ft_chaine(t_redir *redir)
{
	printf("\n");
	while (redir)
	{
		printf("redir type: %d, redir file : %s\n", redir->type, redir->file);
		redir = redir->next;
	}
}

void	ft_show_commands(t_command *commands)
{
	while (commands)
	{
		printf("Commande\n");
		ft_show(commands->args);
		ft_chaine(commands->redirin);
		ft_chaine(commands->redirout);
		commands = commands->next;
		printf("\n");
	}
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	int		res;

	if (ft_check_params(argc, argv, envp) != 0)
		return (2);
	if (ft_init_shell(&shell, envp) != 0)
		return (ft_clean_shell(&shell), 2);
	ft_signal_handler();
	while (1)
	{
		res = ft_parsing(&shell);
		if (res == 2)
			return (ft_clean_shell(&shell), 2);
		if (res == 1)
		{
			ft_clean_line(&shell);
			continue ;
		}
		// ft_show_commands(shell.commands);
		ft_exec(&shell);
		ft_clean_line(&shell);
	}
	rl_clear_history();
	return (ft_clean_shell(&shell), 2);
}
// ft_free_env(shell.env);
// return (shell.exitcode);
