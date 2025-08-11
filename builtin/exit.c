/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:06:16 by anony             #+#    #+#             */
/*   Updated: 2025/08/11 14:59:25 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_numeric(char *value)
{
	int	i;

	i = 0;
	while (value[i] == ' ' || (value[i] >= '\t' && value[i] <= '\r'))
		i++;
	if (ft_isdigit(value[i]) != 1)
		return (1);
	while (ft_isdigit(value[i]) == 1)
		i++;
	while (value[i] == ' ' || (value[i] >= '\t' && value[i] <= '\r'))
		i++;
	if (value[i])
		return (1);
	return (0);
}

int	ft_is_too_long(char *val)
{
	int		start;
	int		end;
	char	*nb;

	start = 0;
	while (val[start] == ' ' || (val[start] >= '\t' && val[start] <= '\r'))
		start++;
	end = start;
	while (ft_isdigit(val[end]) == 1)
		end++;
	end--;
	if (end - start > 18)
		return (1);
	nb = ft_truncate(val, start + 1, end);
	if (ft_atoi(nb) > 223372036854775807 && val[start] == '9')
		return (free(nb), 1);
	free(nb);
	return (0);
}

void	ft_exit_num_fail(void)
{
	g_signal = 1;
	ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
}

int	ft_exit(t_command *command, t_shell *shell, t_savedfds *fds, int sb)
{
	int	code;

	if (!command->args || ft_strncmp(command->args[0], "exit", 5) != 0)
		return (1);
	if (sb == 1)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!command->args[1])
		g_signal = 0;
	else if (command->args[1] && (ft_is_numeric(command->args[1]) != 0
			|| ft_is_too_long(command->args[1]) != 0))
		ft_exit_num_fail();
	else if (command->args[1] && command->args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (g_signal = 1, 1);
	}
	else if (command->args[1] && ft_is_numeric(command->args[1]) == 0)
	{
		code = ft_atoi(command->args[1]) % 256;
		g_signal = code;
	}
	if (ft_restore_savedfd(fds) != 0)
		return (1);
	ft_clean_shell(shell);
	exit(g_signal);
}
