/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:27:16 by anony             #+#    #+#             */
/*   Updated: 2025/08/01 22:10:26 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_free_pipetab(int **tab)
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

int **ft_alloc_pipe_tab(t_shell *shell)
{
	int nbcom;
    int **pipetab;
    int i;

    nbcom = ft_nb_commands(shell);
    pipetab = malloc (nbcom * sizeof(int *));
    if (!pipetab)
        return (NULL);
    i = 0;
    while (i < nbcom - 1)
    {
        pipetab[i] = malloc (3 * sizeof(int));
        if (!pipetab[i])
            return (ft_free_pipetab(pipetab), NULL);
        i++;
    }
    pipetab[i] = NULL;
    return (pipetab);
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






void ft_close_fd(int *fd)
{
	if (*fd == -1)
		return ;
	close(*fd);
	*fd = -1;
	return ;
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


int ft_exec (t_shell *shell)
{
    // int **pipetab;
    // pid_t pid;
    // int i;
	// int nbcom;
	// char *path;
    
	int pipefd[2];
	int prevfd;
	int nbcom;
	int i;
	pid_t pid;
	char *path;
	t_command *command;
    
    // si cest un builtin seul
	if (!shell->commands->next && ft_is_builtin(shell->commands) == 0)
	{
		ft_handle_redir(shell->commands);       ///////////////////////// ajout
		if (ft_exec_builtin (shell->commands, shell) != 0)
			return (1);
		g_signal = 0;
		return (0);
	}
	prevfd = -1;
	i = 0;
	command = shell->commands;
	nbcom = ft_nb_commands(shell);
	while (i < nbcom)
	{
		if (i < nbcom - 1)
			if (pipe(pipefd) == -1)
				return (perror("pipe"), 1);
		fprintf(stderr, "--Dans le main previous : %i\n", prevfd);
		fprintf(stderr, "--Dans le main pipdeds[0] : %i\n", pipefd[0]);
		fprintf(stderr, "--Dans le main pipdeds[1] : %i\n",pipefd[1]);
		
		pid = fork();
		if (pid < 0)
			return (perror("fork"), 1);
        if (pid == 0)
        {
			ft_handle_redir(command);
            if (i != 0)
            {
				fprintf(stderr, "valeur de prevdfd : %i\n", prevfd);
                dup2(prevfd , STDIN_FILENO);
                ft_close_fd(&prevfd);
            }
			ft_close_fd(&pipefd[0]);
            if (i != nbcom - 1)
            {
				fprintf(stderr, "valeur de pipefd[1] : %i\n", pipefd[1]);
                dup2(pipefd[1], STDOUT_FILENO);
            }
			ft_close_fd(&pipefd[1]);
			path = ft_get_path(command, shell);
			if (!path)
			{
				ft_putstr_fd("Command not found\n", STDERR_FILENO);
				exit(127);
			}
			if (execve(path, command->args, shell->env) == -1)
            {
				perror("execve");
                free(path);
                exit(2);
            }
        }
        else if (pid > 0)
        {
            if (i != 0)
                ft_close_fd(&prevfd);
            if (i != nbcom - 1)
                ft_close_fd(&pipefd[1]);
			prevfd = pipefd[0];
            command->pid = pid;
        }
        else
			return (perror("pipe"), 1);
        i++;
		command = command->next;
	}
	if (ft_wait_pids(shell) != 0)
		return (1);
	return (0);
}


	
    // pipetab = ft_alloc_pipe_tab(shell);
    // if (!pipetab)
    //     exit (2);
    // i = 0;
    // nbcom = ft_nb_commands(shell);
    // while (i < nbcom)
    // {
    //     if (i < nbcom - 1)
    //         if (pipe(pipetab[i]) == -1)
    //             {
    //                 perror("pipe");
    //                 ft_free_pipetab(pipetab);
    //                 exit(2);
    //             }
    //     pid = fork();
    //     if (pid < 0)
    //     {
	//         perror("fork failed");
    //         ft_free_pipetab(pipetab);
    //         exit(2);
    //     }
    //     if (pid == 0)
    //     {
    //         if (i != 0)
    //         {
    //             dup2(pipetab[i - 1][0] , STDIN_FILENO);
    //             close(pipetab[i - 1][0]);
    //         }
    //         if (i != nbcom - 1)
    //         {
    //             dup2(pipetab[i][1], STDOUT_FILENO);
    //             close(pipetab[i][1]);
    //         }
	// 		path = ft_get_path(shell);
	// 		if (!path)
	// 		{
	// 			printf("Command not found\n");
    //             ft_free_pipetab(pipetab);
	// 			exit(127);
	// 		}
	// 		printf("%s\n", path);
	// 		if (execve(path, shell->commands->args, shell->env) == -1)
    //         {
	// 			perror("execve");
    //             ft_free_pipetab(pipetab);
            
    //             free(path);
    //             exit(2);
    //         }
    //     }
    //     else if (pid > 0)
    //     {
    //         if (i != 0)
    //             close(pipetab[i - 1][0]);
    //         if (i != nbcom - 1)
    //             close(pipetab[i][1]);
    //         waitpid(pid, NULL, 0);
    //     }
    //     else
    //     {
    //         perror("fork failed");
    //         ft_free_pipetab(pipetab);
    //         exit(2);
    //     }
    //     i++;
    // }
    // ft_free_pipetab(pipetab);
