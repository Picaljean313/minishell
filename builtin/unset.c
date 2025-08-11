/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:06:46 by anony             #+#    #+#             */
/*   Updated: 2025/08/11 15:02:27 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_fill_newenv(int ind, char **newenv, t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (shell->env[j])
	{
		if (j != ind)
		{
			newenv[i] = shell->env[j];
			i++;
			j++;
		}
		else
		j++;
	}
	newenv[i] = NULL;
	free(shell->env[ind]);
	free(shell->env);
	shell->env = newenv;
}

int	ft_unset_env_var(char *var, t_shell *shell)
{
	int		len;
	int		ind;
	char	**newenv;
	char	*varext;

	if (!var)
		return (1);
	varext = ft_strjoin(var, "=");
	if (!varext)
		return (1);
	len = 0;
	ind = -1;
	while (shell->env[len])
	{
		if (ft_strncmp(shell->env[len], varext, (int)ft_strlen(varext)) == 0)
			ind = len;
		len++;
	}
	if (ind == -1)
		return (free(varext), 0);
	newenv = malloc (len * sizeof(char *));
	if (!newenv)
		return (free(varext), 1);
	ft_fill_newenv(ind, newenv, shell);
	return (free(varext), 0);
}

void	ft_fill_newexport(int ind, char **newexport, t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (shell->export[j])
	{
		if (j != ind)
		{
			newexport[i] = shell->export[j];
			i++;
			j++;
		}
		else
		j++;
	}
	newexport[i] = NULL;
	free(shell->export[ind]);
	free(shell->export);
	shell->export = newexport;
}

int	ft_unset_export_var(char *var, t_shell *shell)
{
	int		len;
	int		ind;
	char	**newexport;
	char	*varext;

	if (!var)
		return (1);
	varext = ft_strjoin("declare -x ", var);
	if (!varext)
		return (1);
	len = -1;
	ind = -1;
	while (shell->export[++len])
		if (ft_strncmp(shell->export[len], varext, (int)ft_strlen(varext)) == 0
			&& (!shell->export[len][(int)ft_strlen(varext)]
			|| shell->export[len][(int)ft_strlen(varext)] == '='))
			ind = len;
	if (ind == -1)
		return (free(varext), 0);
	newexport = malloc (len * sizeof(char *));
	if (!newexport)
		return (free(varext), 1);
	ft_fill_newexport(ind, newexport, shell);
	return (free(varext), 0);
}

int	ft_unset(t_command *command, t_shell *shell)
{
	int	i;

	if (!command->args || ft_strncmp(command->args[0], "unset", 6) != 0)
		return (1);
	if (!command->args[1])
		return (g_signal = 0, 0);
	i = 1;
	while (command->args[i])
	{
		if (ft_check_unset_var(command->args[i]) != 0)
			return (g_signal = 0, 0);
		if (ft_unset_env_var(command->args[i], shell) != 0)
			return (1);
		if (ft_unset_export_var(command->args[i], shell) != 0)
			return (1);
		i++;
	}
	return (g_signal = 0, 0);
}
