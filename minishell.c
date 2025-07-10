/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:52:09 by anony             #+#    #+#             */
/*   Updated: 2025/07/10 13:27:14 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO

/*
Toujours verifier si une variable d environnement existe et penser a la creer si besoin.

mettre le dossier dans lequel on se situe dans le prompt
*/


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
    ft_signal_handler();
    
    while (1)
    {
        input = readline("minishell_oh_yeah$ ");
        if (!input)
            break ;
        if (*input != '\0')
        {
            i = 0;
            add_history(input);
            if (ft_check(input) != 0)
            {
                if (ft_check(input) == 1)
                    fprintf(stderr, "Operator error\n");
                if (ft_check(input) == 2)
                    fprintf(stderr, "Quotes error\n");
                continue; 
            }
            // while (i < (int)ft_strlen(input))
            //     ft_next_token_value(input, &i);
            ft_show_tokentab(ft_lexer(input));
        }
        free(input);
    }
    rl_clear_history();
    return (0);
}

