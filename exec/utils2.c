/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:38:44 by anony             #+#    #+#             */
/*   Updated: 2025/08/08 16:03:49 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_create_path(char *path, char *cmd)
{
	char	*temp;
	char	*cmdpath;

	temp = ft_strjoin(path, "/");
	if (!temp)
		return (NULL);
	cmdpath = ft_strjoin(temp, cmd);
	free(temp);
	return (cmdpath);
}

void	ft_free_split_path(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return ;
}

char	*ft_get_path(t_command *command, t_shell *shell)
{
	t_exut	vars;

	if (!command || !command->args || !command->args[0])
		return (NULL);
	if (command->args[0][0] == '/' && command->args[0][1])
		return (ft_strdup(command->args[0]));
	vars.path = ft_getenv("PATH", shell->env);
	if (!vars.path)
		return (NULL);
	vars.splitpath = ft_split(vars.path, ':');
	if (!vars.splitpath)
		return (free(vars.path), NULL);
	free(vars.path);
	vars.cmd = command->args[0];
	vars.i = 0;
	while (vars.splitpath[vars.i])
	{
		vars.cmdpath = ft_create_path(vars.splitpath[vars.i], vars.cmd);
		if (access(vars.cmdpath, X_OK) != 0)
			free(vars.cmdpath);
		else
			return (ft_free_split_path(vars.splitpath), vars.cmdpath);
		vars.i++;
	}
	return (ft_free_split_path(vars.splitpath), NULL);
}

void	ft_close_command_heredoc(t_command *command)
{
	t_redir	*redir;

	if (!command)
		return ;
	redir = command->redir;
	while (redir)
	{
		if (redir->heredocfd != -1)
			ft_close_fd(&redir->heredocfd);
		redir = redir->next;
	}
}

void	ft_close_heredoc(t_shell *shell)
{
	t_redir		*redir;
	t_command	*command;

	if (!shell || !shell->commands)
		return ;
	command = shell->commands;
	while (command)
	{
		redir = command->redir;
		while (redir)
		{
			if (redir->heredocfd != -1)
				ft_close_fd(&redir->heredocfd);
			redir = redir->next;
		}
		command = command->next;
	}
}
