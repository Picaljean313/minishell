/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:52:09 by anony             #+#    #+#             */
/*   Updated: 2025/07/07 20:15:32 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO

/*
Toujours verifier si une variable d environnement existe et penser a la creer si besoin.

mettre le dossier dans lequel on se situe dans le prompt
*/

void ft_set_shlvl(char **env)
{
    int i;
    int lvl;
    char *new_lvl;

    i = 0;
    while (env[i])
    {
        if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
        {
            lvl = ft_atoi(env[i] + 6) + 1;
            free(env[i]);
            new_lvl = ft_itoa(lvl);
            env[i] = ft_strjoin("SHLVL=", new_lvl);
            free(new_lvl);
            return ;
        }
        i++;
    }
    return ;
}

char **ft_set_env(char **env)
{
    int i;
    int j;
    char **env_copy;

    i = 0;
    while (env[i])
        i++;
    env_copy = malloc ((i + 1) * sizeof(char *));
    if (!env_copy)
        return (NULL);
    j = 0;
    while (j < i)
    {
        env_copy[j] = ft_strdup(env[j]);
        if (!env_copy[j])
        {
            while (j > 0)
            {
                free(env_copy[j - 1]);
                j--;
            }
            free(env_copy);
            return (NULL);
        }
        j++;
    }
    env_copy[j] = NULL;
    ft_set_shlvl(env_copy);
    return (env_copy);
}

void ft_handle_sigint(int sig)
{
    (void)sig;
    
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
    write(1, "\nminishell_oh_yeah$ ", 20);
    return ;
}

void ft_handle_sigquit(int sig)
{
    (void)sig;
}

int main (int argc, char **argv, char **envp)
{
    char *input;
    char **minishell_env;
    int i;
    
    if (argc != 1 || !argv)
    {
        printf("No arguments allowed\n");
        return (0);
    }
    minishell_env = ft_set_env(envp);
    if (!minishell_env)
    {
        printf("Env allocation failed\n");
        return (0);
    }

    i = 0;
    while (minishell_env[i])
    {
        printf("%s\n", minishell_env[i]);
        i++;
    }
    printf("\n\n\n\n%s\n", getenv("PATH"));
    
    signal(SIGINT, ft_handle_sigint);
    signal(SIGQUIT, ft_handle_sigquit);
    
    while (1)
    {
        input = readline("minishell_oh_yeah$ ");
        if (!input)
            break ;
        if (*input != '\0')
            add_history(input);
        free(input);
    }
    rl_clear_history();
    return (0);
}