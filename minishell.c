/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:52:09 by anony             #+#    #+#             */
/*   Updated: 2025/07/23 12:57:15 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int g_signal = 0;



void ft_show_tokentab(t_token **tab)
{
    t_token *token;

    token = *tab;
    while (token)
    {
        printf("enum : %d\n", token->type);
        printf("value : %s\n", token->value);
        token = token->next;
    }
    return ;
}


int main (int argc, char **argv, char **envp)
{
    t_shell shell;

    
    
    int i;
    
    if (ft_check_params(argc, argv, envp) != 0)
        return (2);
    if (ft_init_shell(&shell, envp) != 0)
        return (2);
    ft_signal_handler();
    while (1)
    {
        shell.input = readline("minishell_oh_yeah$ ");
        if (!shell.input)
            break ;
        add_history(shell.input);
        // if (ft_replace_vars(&shell) != 0)
        //     break ;
        if (ft_check_input(shell.input) != 0)
        {
            printf("Your input sucks\n");
            continue ;
        }
        shell.tokens = ft_lexer(&shell);
        if (!shell.tokens)
        {
            printf("Lexer failed\n");
            continue ;
        }
        if (ft_expand(&shell) != 0)
        {
            printf("Expand failed\n");
            continue ;
        }
        if (ft_check_pipes(shell.tokens) != 0)
        {
            printf("Your pipes sucks\n");
            continue ;
        }
        shell.pipes = ft_parser(shell.tokens);
        if (!shell.tokens)
        {
            printf("Parser failed\n");
            continue ;
        }

            
        // ft_show_tokentab(shell.tokens);

        

    }
    rl_clear_history();
    return (shell.exitcode);



    
    i = 0;
    while (shell.env[i])
    {
        printf("%s\n", shell.env[i]);
        i++;
    }
    printf("%s\n", ft_getenv("PATH", shell.env));

    ft_clean_shell(&shell);

    

    
}





/*
Succès	0
Commande introuvable	127
Permission refusée	126
Mauvaise syntaxe (parse error)	2 (souvent)
Échec d’une commande normale	1
Signaux (ex: SIGINT)	128 + N (N = numéro du signal)
*/



//     char *input;
//     char **minishell_env;
    
//     int i;
//     t_token **tab;
    
//     if (argc != 1 || !argv)
//     {
//         printf("No arguments allowed\n");
//         return (0);
//     }
//     minishell_env = ft_set_env(envp);
//     if (!minishell_env)
//     {
//         printf("Env allocation failed\n");
//         return (0);
//     }

//     i = 0;
//     ft_signal_handler();
    
//     while (1)
//     {
//         input = readline("minishell_oh_yeah$ ");
//         if (!input)
//             break ;
//         if (*input != '\0')
//         {
//             i = 0;
//             add_history(input);
//             i = ft_check(input);
//             if (i != 0)
//             {
//                 if (i == 1)
//                     fprintf(stderr, "Operator error\n");
//                 if (i == 2)
//                     fprintf(stderr, "Quotes error\n");
//                 continue; 
//             }
//             tab = ft_lexer(input);
//             ft_show_tokentab(tab);
//             i = ft_check_pipes(tab);
//             ft_parser(tab);
//             ft_expand(tab, minishell_env);
//         }
//         free(input);
//     }
//     rl_clear_history();
//     return (0);
// }
