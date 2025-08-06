/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:06:46 by anony             #+#    #+#             */
/*   Updated: 2025/08/06 20:00:14 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_check_unset_var(char *var)
{
    int i;

    if (!(ft_isalpha(var[0]) == 1 || var[0] == '_'))
        return (1);
    i = 1;
    while (var[i] == '_' || ft_isalnum(var[i]) == 1)
        i++;
    if (var[i] != '\0')
        return (1);
    return (0);
}

void ft_fill_newenv(int ind, char **newenv,t_shell *shell)
{
    int i;
    int j;

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

int ft_unset_env_var(char *var, t_shell *shell)
{
    int len;
	int		ind;
    char **newenv;
    char *varext;

    if (!var)
        return (1);
    if (ft_check_unset_var(var) != 0)
        return (ft_putstr_fd("Wrong argument\n", STDERR_FILENO), 0);
    varext = ft_strjoin(var, "=");
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


int ft_unset(t_command *command, t_shell *shell)
{
    int i;

    if (!command->args || ft_strncmp(command->args[0], "unset", 6) != 0)
		return (1);
	if (!command->args[1])
		return (0);
    i = 1;
    while (command->args[i])
    {
        ft_unset_env_var(command->args[i], shell);
        i++;
    }
    return (0);
}
  