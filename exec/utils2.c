/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:38:44 by anony             #+#    #+#             */
/*   Updated: 2025/08/11 20:18:24 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_case_point(t_exec *ex)
{
	char	*pwd;
	char	*value;
	char	*path;

	if (ex->command->args[0][1] == '/')
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return (NULL);
		value = ft_strjoin(pwd, (ex->command->args[0] + 1));
		free(pwd);
		return (value);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	value = ft_strjoin(pwd, "/");
	free(pwd);
	if (!value)
		return (NULL);
	path = ft_strjoin(value, ex->command->args[0]);
	free(value);
	if (!path)
		return (NULL);
	return (path);
}

char	*ft_set_abs_rel_path(t_exec *ex, t_shell *shell)
{
	int	i;

	if (!ex->command || !ex->command->args || !ex->command->args[0]
		|| (ex->command->args[0][0] != '/' && ex->command->args[0][0] != '.'))
		return (NULL);
	i = 0;
	while (ex->command->args[0][i] == '/')
		i++;
	if (i > 0 && !ex->command->args[0][i])
	{
		ft_putstr_fd("/: Is a directory\n", STDERR_FILENO);
		g_signal = 126;
		ft_close_heredoc(shell);
		ft_clean_shell(shell);
		free(ex);
		exit(126);
		return (NULL);
	}
	if (i > 0 && ex->command->args[0][i])
		return (ft_strdup(ex->command->args[0] + i - 1));
	if (ex->command->args[0][0] == '.')
		return (ft_case_point(ex));
	return (NULL);
}

// char	*ft_set_abs_rel_path(t_exec *ex, t_shell *shell)
// {
// 	char *pwd;
// 	char *value;

// 	if (!ex->command || !ex->command->args || !ex->command->args[0]
// 		|| (ex->command->args[0][0] != '/' && ex->command->args[0][0] != '.'))
// 		return (NULL);
// 	if (ex->command->args[0][0] == '/' && !ex->command->args[0][1])
// 	{
// 		ft_putstr_fd("/: Is a directory\n", STDERR_FILENO);
// 		g_signal = 126;
// 		ft_close_heredoc(shell);
// 		ft_clean_shell(shell);
// 		free(ex);
// 		exit(126);
// 		return (NULL);
// 	}
// 	if (ex->command->args[0][0] == '/')
// 		return (ft_strdup(ex->command->args[0]));
// 	if (ex->command->args[0][0] == '.' && ex->command->args[0][1] == '/')
// 	{
// 		pwd = getcwd(NULL, 0);
// 		if (!pwd)
// 			return (NULL);
// 		value = ft_strjoin(pwd, (ex->command->args[0] + 1));
// 		free(pwd);
// 		return (value);
// 	}
// 	if (ex->command->args[0][0] == '.')
// 	{
// 		pwd = getcwd(NULL, 0);
// 		if (!pwd)
// 			return (NULL);
// 		value = ft_strjoin(pwd, "/");
// 		free(pwd);
// 		if (!value)
// 			return (NULL);
// 		pwd = ft_strjoin(value, ex->command->args[0]);
// 		free(value);
// 		if (!pwd)
// 			return (NULL);
// 		return (pwd);
// 	}
// 	return (NULL);
// }

char	*ft_get_path(t_exec *ex, t_shell *shell)
{
	t_exut	vars;

	if (!ex->command || !ex->command->args || !ex->command->args[0])
		return (NULL);
	if (ex->command->args[0][0] == '/' || ex->command->args[0][0] == '.')
		return (ft_set_abs_rel_path(ex, shell));
	vars.path = ft_getenv("PATH", shell->env);
	if (!vars.path)
		return (NULL);
	vars.splitpath = ft_split(vars.path, ':');
	if (!vars.splitpath)
		return (free(vars.path), NULL);
	free(vars.path);
	vars.cmd = ex->command->args[0];
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
