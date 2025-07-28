/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:31:15 by anony             #+#    #+#             */
/*   Updated: 2025/07/26 17:36:11 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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