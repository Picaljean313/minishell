/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exectest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:31:15 by anony             #+#    #+#             */
/*   Updated: 2025/08/04 15:55:58 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
		if (ft_exec_builtin (shell->commands, shell) != 0)
			exit (2) ;
		g_signal = 0;
		return ;
	}
	return ;
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


/*
POUR GERER LES HEREDOCS

tu fork (juste apres le lexing, de tte facon tu lattends avant la suite) et tu readline (boucle
 comme dans le main et tu check que ton input egal le delimiteur). tu stock les differentes lignes (liste chainee)
  

*/


/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_CMDS 3

int main(void)
{
    char *cmds[MAX_CMDS][4] = {
        {"ls", NULL},
        {"grep", ".c", NULL},
        {"wc", "-l", NULL}
    };

    int i;
    int pipefd[2];
    int prev_fd = -1;

    for (i = 0; i < MAX_CMDS; i++)
    {
        if (i < MAX_CMDS - 1)
            pipe(pipefd); // Crée un nouveau pipe pour les 2 prochaines commandes

        pid_t pid = fork();
        if (pid == 0)
        {
            // STDIN ← prev_fd si ce n’est pas la première commande
            if (prev_fd != -1)
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }

            // STDOUT → pipefd[1] si ce n’est pas la dernière commande
            if (i < MAX_CMDS - 1)
            {
                close(pipefd[0]); // Ferme lecture
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
            }

            execvp(cmds[i][0], cmds[i]);
            perror("execvp");
            exit(EXIT_FAILURE);
        }

        // Parent
        if (prev_fd != -1)
            close(prev_fd); // Ferme ancienne lecture

        if (i < MAX_CMDS - 1)
        {
            close(pipefd[1]);     // Ferme écriture
            prev_fd = pipefd[0];  // Garde lecture pour la prochaine commande
        }
    }

    // Attente de tous les enfants
    for (i = 0; i < MAX_CMDS; i++)
        wait(NULL);

    return 0;
}

*/


// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/wait.h>

// int main(void)
// {
//     // Commandes à exécuter (tableau de tableaux de chaînes)
//     // Chaque commande est un tableau de strings, terminé par NULL
//     char *cmds[3][4] = {
//         {"ls", "-l", NULL},
//         {"grep", ".c", NULL},
//         {"wc", "-l", NULL}
//     };

//     int pipe1[2]; // pipe entre cmd1 et cmd2
//     int pipe2[2]; // pipe entre cmd2 et cmd3

//     pid_t pid1, pid2, pid3;

//     // Création du premier pipe (cmd1 -> cmd2)
//     if (pipe(pipe1) == -1) {
//         perror("pipe1");
//         exit(EXIT_FAILURE);
//     }

//     pid1 = fork();
//     if (pid1 < 0) {
//         perror("fork1");
//         exit(EXIT_FAILURE);
//     }

//     if (pid1 == 0) {
//         // ----- Processus cmd1 -----
//         // Rediriger stdout vers pipe1[1]
//         close(pipe1[0]);          // Ferme la lecture (cmd1 n’en a pas besoin)
//         dup2(pipe1[1], STDOUT_FILENO);
//         close(pipe1[1]);

//         // cmd1 ne lit rien de stdin, garde stdin par défaut
//         execvp(cmds[0][0], cmds[0]);
//         perror("execvp cmd1");
//         exit(EXIT_FAILURE);
//     }

//     // Parent continue, crée pipe2 pour cmd2 -> cmd3
//     if (pipe(pipe2) == -1) {
//         perror("pipe2");
//         exit(EXIT_FAILURE);
//     }

//     pid2 = fork();
//     if (pid2 < 0) {
//         perror("fork2");
//         exit(EXIT_FAILURE);
//     }

//     if (pid2 == 0) {
//         // ----- Processus cmd2 -----
//         // Rediriger stdin depuis pipe1[0]
//         dup2(pipe1[0], STDIN_FILENO);
//         close(pipe1[0]);

//         // Rediriger stdout vers pipe2[1]
//         close(pipe2[0]);
//         dup2(pipe2[1], STDOUT_FILENO);
//         close(pipe2[1]);

//         // cmd2 doit fermer pipe1[1] (non utilisé)
//         close(pipe1[1]);

//         execvp(cmds[1][0], cmds[1]);
//         perror("execvp cmd2");
//         exit(EXIT_FAILURE);
//     }

//     // Dans le parent, on ferme pipe1[0] et pipe1[1] (plus utilisés)
//     close(pipe1[0]);
//     close(pipe1[1]);

//     pid3 = fork();
//     if (pid3 < 0) {
//         perror("fork3");
//         exit(EXIT_FAILURE);
//     }

//     if (pid3 == 0) {
//         // ----- Processus cmd3 -----
//         // Rediriger stdin depuis pipe2[0]
//         dup2(pipe2[0], STDIN_FILENO);
//         close(pipe2[0]);

//         // cmd3 écrit sur stdout normal
//         close(pipe2[1]);

//         execvp(cmds[2][0], cmds[2]);
//         perror("execvp cmd3");
//         exit(EXIT_FAILURE);
//     }

//     // Dans le parent, on ferme pipe2[0] et pipe2[1] (plus utilisés)
//     close(pipe2[0]);
//     close(pipe2[1]);

//     // On attend que tous les enfants terminent
//     waitpid(pid1, NULL, 0);
//     waitpid(pid2, NULL, 0);
//     waitpid(pid3, NULL, 0);

//     return 0;
// }


/*


✅ 1. FONCTIONS ESSENTIELLES POUR exec DANS UN MINISHELL
| Fonction           | Rôle dans `exec`                                          |               
| ------------------ | --------------------------------------------------------- | 
| **write**          | Affiche des messages, erreurs, ou simule `echo`           |               
| **access**         | Vérifie si la commande existe et est exécutable (`$PATH`) |               
| **open**           | Ouvre des fichiers pour `<`, `>`, `>>` redirections       |               
| **read**           | Lire dans un fichier ou stdin (utile pour `heredoc`)      |               
| **close**          | Ferme les descripteurs inutiles (après `dup2`, `pipe`)    |               
| **fork**           | Crée un processus fils pour exécuter une commande         |               
| **wait / waitpid** | Synchronise le parent avec le fils (attend fin exec)      |               
| **execve**         | Lance la commande (remplace le processus fils)            |               
| **dup / dup2**     | Redirige `stdin`/`stdout` pour `<`, `>`, `               | 
| **pipe**           | Crée une communication entre processus pour gérer les `  |             

🔹 Ces fonctions sont la base même de la gestion d’un exec dans un minishell.

🟡 2. UTILES DANS CERTAINS CAS (BUILTINS, ENV, CD, etc.)

| Fonction              | Rôle                                                                                      |
| --------------------- | ----------------------------------------------------------------------------------------- |
| **exit**              | Implémente la commande `exit`                                                             |
| **getcwd**            | Utile pour `pwd` et `cd` (afficher le chemin actuel)                                      |
| **chdir**             | Implémente `cd` pour changer de dossier                                                   |
| **stat/lstat/fstat**  | Pour info sur fichiers (utile pour certaines commandes comme `ls`, ou checks approfondis) |
| **unlink**            | Implémente `rm` ou supprime un fichier temporaire                                         |
| **getenv**            | Accède aux variables d’environnement (comme `$PATH`)                                      |
| **perror / strerror** | Affiche proprement les erreurs système                                                    |

🔸 Tu les utilises pour implémenter les built-ins (cd, exit, pwd), gérer les env vars, ou afficher les erreurs propres.

❌ 3. PAS UTILES POUR L’exec DANS UN MINISHELL DE BASE

| Fonction                                              | Pourquoi inutile ici ?                                                                                                 |
| ----------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------- |
| **wait3 / wait4**                                     | Versions avancées de `wait`, peu utiles en shell simple                                                                |
| **kill**                                              | Sert à envoyer des signaux, utile pour `kill`, mais pas pour `exec`                                                    |
| **isatty, ttyname, ttyslot, ioctl**                   | Gèrent les terminaux, pas nécessaire pour `exec`                                                                       |
| **opendir / readdir / closedir**                      | Pour lire le contenu d’un répertoire (utile pour `ls`, mais pas dans `exec` directement)                               |
| **tcsetattr / tcgetattr**                             | Gèrent les attributs du terminal (utile pour `ctrl+C`, pas pour `exec`)                                                |
| **tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs** | Viennent de termcap : pour gérer des interfaces terminales avancées (ex: `ncurses`) – inutile pour un minishell simple |

✅ En résumé : pour gérer exec dans un minishell, tu dois maîtriser ces fonctions :

🔹 Obligatoires :

    fork, execve, dup2, pipe, wait / waitpid

    open, close, access, read, write

🔸 Fortement recommandées :

    getenv (pour $PATH)

    perror (affichage d'erreurs système)

    exit (terminer un shell proprement)

*/