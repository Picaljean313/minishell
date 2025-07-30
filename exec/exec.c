/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:27:16 by anony             #+#    #+#             */
/*   Updated: 2025/07/30 16:16:54 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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


char *ft_get_path (t_shell *shell)
{
	char *path;
	char **splitpath;
	char *cmdpath;
	char *cmd;
	int i;

	path = ft_getenv("PATH", shell->env);
	if (!path)
		return (NULL);
	splitpath = ft_split(path, ':');
	if (!splitpath)
		return (free(path), NULL);
	free(path);
	cmd = shell->commands->args[0];
	i = 0;
	while (splitpath[i])
	{
		cmdpath = ft_create_path(splitpath[i], cmd);
		if (access(cmdpath, X_OK) != 0)
			free(cmdpath);
		else
			return (cmdpath);
		i++;
	}
	return (NULL);
}

/*
| Code      | Signification conventionnelle                                                       |
| --------- | ----------------------------------------------------------------------------------- |
| `0`       | ✅ Succès (tout s'est bien passé)                                                    |
| `1`       | ❌ Erreur générique (échec simple)                                                   |
| `2`       | ❌ Mauvais usage d'une commande (mauvais arguments)                                  |
| `126`     | ❌ Commande trouvée mais non exécutable                                              |
| `127`     | ❌ Commande introuvable                                                              |
| `128 + N` | ❌ Processus terminé par le **signal `N`** (ex. `130` = `SIGINT`, `131` = `SIGQUIT`) |
| `> 128`   | Souvent associé à une **fin anormale** du processus                                 |
| `255`     | ❌ Erreur fatale ou sortie manuelle avec `exit(255)`                                 |

*/

int ft_exec_builtin(t_command *command, t_shell *shell)
{
    if (!command->args)
		return (2);
	if (ft_strncmp(command->args[0], "cd", 3) == 0)
		if (ft_cd(command, shell) != 0)
			return (1);
	// if (ft_strncmp(command->args[0], "echo", 5) == 0)
	// 	if (ft_echo(command, shell) != 0)
	// 		return (1);
	// if (ft_strncmp(command->args[0], "env", 4) == 0)
	// 	if (ft_env(command, shell) != 0)
	// 		return (1);
	// if (ft_strncmp(command->args[0], "exit", 5) == 0)
	// 	if (ft_exit(command, shell) != 0)
	// 		return (1);
	// if (ft_strncmp(command->args[0], "export", 7) == 0)
	// 	if (ft_export(command, shell) != 0)
	// 		return (1);
	// if (ft_strncmp(command->args[0], "pwd", 4) == 0)
	// 	if (ft_pwd(command, shell) != 0)
	// 		return (1);
	// if (ft_strncmp(command->args[0], "unset", 6) == 0)
	// 	if (ft_unset(command, shell) != 0)
	// 		return (1);
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

/*
int prev_fd = -1;

for (int i = 0; i < n_cmds; ++i) {
    int pipefd[2];
    if (i < n_cmds - 1) {
        pipe(pipefd);
    }

    pid_t pid = fork();

    if (pid == 0) {
        if (prev_fd != -1) {
            dup2(prev_fd, STDIN_FILENO);
            close(prev_fd);
        }
        if (i < n_cmds - 1) {
            dup2(pipefd[1], STDOUT_FILENO);
            close(pipefd[0]);
            close(pipefd[1]);
        }
        exec_command(cmds[i]); // execve or builtin
        exit(1); // en cas d’échec
    } else {
        if (prev_fd != -1)
            close(prev_fd);
        if (i < n_cmds - 1)
            close(pipefd[1]);

        prev_fd = (i < n_cmds - 1) ? pipefd[0] : -1;
    }
}

// attendre tous les enfants
for (int i = 0; i < n_cmds; ++i)
    wait(NULL);

*/

/*
int fd;

if (redir->type == REDIR_IN) {
    fd = open(redir->filename, O_RDONLY);
    dup2(fd, STDIN_FILENO);
    close(fd);
}
else if (redir->type == REDIR_OUT) {
    fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    dup2(fd, STDOUT_FILENO);
    close(fd);
}
else if (redir->type == REDIR_APPEND) {
    fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    dup2(fd, STDOUT_FILENO);
    close(fd);
}
else if (redir->type == REDIR_HEREDOC) {
    // Lire l'entrée jusqu'au délimiteur, stocker dans un pipe ou fichier temporaire
    // puis dup2(pipe_read_end, STDIN_FILENO)
}


.... qund gerer les redirs :
pid = fork();
if (pid == 0) {
    apply_redirections(cmd->redirs); // dup2() ici
    exec_command(cmd); // execve ou exec_builtin
    exit(1);
}

*/


/*

| Étape | Action                                          |
| ----- | ----------------------------------------------- |
| 1     | Compter les commandes dans le pipe              |
| 2     | Créer `N - 1` pipes                             |
| 3     | Pour chaque commande, `fork()`                  |
| 4     | Rediriger `stdin` / `stdout` selon la position  |
| 5     | Fermer les pipes inutiles dans chaque processus |
| 6     | Dans le parent, `wait()` pour tous les enfants  |


*/

void ft_exec (t_shell *shell)
{
	char *path;
	pid_t pid;
    // t_command *command;
	
    // si cest un builtin seul
	if (!shell->commands->next && ft_is_builtin(shell->commands) == 0)
	{
		printf("ok\n");
		if (ft_exec_builtin (shell->commands, shell) != 0)
			exit (1) ;
		// exit (0);
		return ;
	}
	
	pid = fork();

	if (pid == 0)
	{
		if (!shell->commands->args)
		{
			// A TRAITER
		}
		else
		{
			path = ft_get_path(shell);
			if (!path)
			{
				printf("Command not found\n");
				return ;
			}
			printf("%s\n", path);
			if (execve(path, shell->commands->args, shell->env) == -1)
				perror("execve");
		}
	}
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
	}
	else
	{
		perror("fork failed");
	}
}