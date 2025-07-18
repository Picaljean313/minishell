/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:52:09 by anony             #+#    #+#             */
/*   Updated: 2025/07/18 12:48:07 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int g_signal = 0;

int main (int argc, char **argv, char **envp)
{
    t_shell shell;

    
    
    int i;
    

    
    ft_init_shell(&shell, envp);
    i = 0;
    while (shell.env[i])
    {
        printf("%s\n", shell.env[i]);
        i++;
    }
    printf("%s\n", ft_getenv("PATH", shell.env));

    ft_clean_shell(&shell);

    

    
    (void)argc;
    (void)argv;

}






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
