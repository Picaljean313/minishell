/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:00:19 by anony             #+#    #+#             */
/*   Updated: 2025/07/09 17:56:56 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef enum e_token_type
{
    WORD,
    STRING,
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    HEREDOC,
    APPEND
} t_token_type;

typedef struct s_token
{
    t_token_type type;
    char *value;
    struct s_token *next;
} t_token;

// initialization.c

void ft_set_shlvl(char **env);
char **ft_set_env(char **env);

// signalhandler.c

void ft_handle_sigint(int sig);
void ft_handle_sigquit(int sig);
void ft_signal_handler();

// lexer.c

void ft_add_token(t_token **tab, t_token_type type, char *value);
int ft_check_wrong_operator(char *input, int ind);
int ft_check(char *input);
char *ft_truncate(char *str, int start, int end);
char *ft_next_token_value(char *input, int *ind);

#endif