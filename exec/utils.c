/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:29:40 by anony             #+#    #+#             */
/*   Updated: 2025/08/05 12:47:28 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_close_fd(int *fd)
{
	if (*fd == -1)
		return ;
	close(*fd);
	*fd = -1;
	return ;
}

int ft_is_builtin(t_command *command)
{
    if (!command->args)
		return (1);
	if (ft_strncmp(command->args[0], "echo", 5) == 0)
		return (0);
	if (ft_strncmp(command->args[0], "cd", 3) == 0)
		return (0);
	if (ft_strncmp(command->args[0], "pwd", 4) == 0)
		return (0);
	if (ft_strncmp(command->args[0], "export", 7) == 0)
		return (0);
	if (ft_strncmp(command->args[0], "unset", 6) == 0)
		return (0);
	if (ft_strncmp(command->args[0], "env", 4) == 0)
		return (0);
	if (ft_strncmp(command->args[0], "exit", 5) == 0)
		return (0);
    return (1);
}


int ft_exec_builtin(t_command *command, t_shell *shell)
{
    if (!command->args)
		return (2);
	if (ft_strncmp(command->args[0], "cd", 3) == 0)
		if (ft_cd(command, shell) != 0)
			return (1);
	if (ft_strncmp(command->args[0], "echo", 5) == 0)
		if (ft_echo(command) != 0)
			return (1);
	if (ft_strncmp(command->args[0], "env", 4) == 0)
		if (ft_env(command, shell) != 0)
			return (1);
	if (ft_strncmp(command->args[0], "exit", 5) == 0)
		if (ft_exit(command) != 0)
			return (1);
	if (ft_strncmp(command->args[0], "export", 7) == 0)
		if (ft_export(command, shell) != 0)
			return (1);
	if (ft_strncmp(command->args[0], "pwd", 4) == 0)
		if (ft_pwd(command) != 0)
			return (1);
	if (ft_strncmp(command->args[0], "unset", 6) == 0)
		if (ft_unset(command, shell) != 0)
			return (1);
    return (0);
}


int ft_wait_pids(t_shell *shell)
{
	t_command *command;

	command = shell->commands;
	while (command)
	{
		if (waitpid(command->pid, NULL, 0) == -1)
			return (perror("waitpid"), 1);
		command = command->next;
	}
	return (0);
}

int ft_nb_commands(t_shell *shell)
{
	t_command * command;
    int nbcom;
    
    nbcom = 0;
    command = shell->commands;
	while (command)
	{
		command = command->next;
		nbcom++;
	}
    return (nbcom);
}


char *ft_create_path(char *path, char *cmd)
{
	char *temp;
	char *cmdpath;
	
	temp = ft_strjoin(path, "/");
	if (!temp)
		return (NULL);
	cmdpath = ft_strjoin(temp, cmd);
	free(temp);
	return (cmdpath);
}

void ft_free_split_path(char **tab)
{
    int i;

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

char *ft_get_path (t_command *command, t_shell *shell)
{
	char *path;
	char **splitpath;
	char *cmdpath;
	char *cmd;
	int i;

    if (command->args[0][0] == '/')
    {
        cmdpath = ft_strdup(command->args[0]);
        return (cmdpath);
    }
	path = ft_getenv("PATH", shell->env);
	if (!path)
		return (NULL);
	splitpath = ft_split(path, ':');
	if (!splitpath)
		return (free(path), NULL);
	free(path);
	cmd = command->args[0];
	i = 0;
	while (splitpath[i])
	{
		cmdpath = ft_create_path(splitpath[i], cmd);
		if (access(cmdpath, X_OK) != 0)
			free(cmdpath);
		else
			return (ft_free_split_path(splitpath), cmdpath);
		i++;
	}
	return (ft_free_split_path(splitpath), NULL);
}

void ft_close_heredoc(t_command *command)
{
	t_redir *redir;

	redir = command->redir;
	while (redir)
	{
		if (redir->heredocfd != -1)
			ft_close_fd(&redir->heredocfd);
		redir = redir->next;
	}
}
