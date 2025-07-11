/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:00:19 by anony             #+#    #+#             */
/*   Updated: 2025/07/11 17:18:34 by anony            ###   ########.fr       */
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
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    REDIR_HEREDOC,
    REDIR_APPEND
} t_token_type;

typedef struct s_token
{
    t_token_type type;
    char *value;
    struct s_token *next;
} t_token;

// typedef enum e_redir_type
// {
//     REDIR_IN,
//     REDIR_OUT,
//     REDIR_HEREDOC,
//     REDIR_APPEND
// } t_redir_type;

typedef struct s_redir
{
    t_token_type type;
    char *file;
    struct s_redir *next;
} t_redir;

// typedef struct s_pipe_tokens
// {
//     char **tabtokens;
//     struct s_pipe_tokens next;
// } t_pipe_tokens;

typedef struct s_pipe
{
    char *cmd;
    char **args;
    t_redir *redirin;
    t_redir *redirout;
    struct s_pipe *next;
} t_pipe;

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
t_token_type ft_get_token_type(char *value);
t_token **ft_lexer(char *input);
void ft_show_tokentab(t_token **tab);

// parser.c

int ft_check_empty_pipes(t_token **tab);
int ft_check_pipe(t_token *token);
int ft_check_pipes(t_token **tab);

#endif