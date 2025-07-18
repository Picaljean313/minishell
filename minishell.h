/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:00:19 by anony             #+#    #+#             */
/*   Updated: 2025/07/18 18:49:32 by anony            ###   ########.fr       */
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

extern int	g_signal;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_HEREDOC,
	REDIR_APPEND
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_pipe
{
	char			*cmd;
	char			**args;
	t_token			*token;
	t_redir			*redirin;
	t_redir			*redirout;
	struct s_pipe	*next;
}	t_pipe;

typedef struct s_shell
{
	char	*input;
	char	**env;
	t_token	**tokens;
	t_pipe	**pipes;
	int		exitcode;
}	t_shell;

// initshell.c

int ft_check_params(int argc, char **argv, char **env);
int	ft_init_shell(t_shell *shell, char **envp);

// setenv.c

int	ft_set_shlvl(char **env);
char	**ft_set_env(char **env);

// cleanshell.c

void ft_free_env(char **env);
void ft_free_token_tab(t_token **tokentab);
void ft_clean_shell(t_shell *shell);

// utils.c

char *ft_truncate(char *str, int start, int end);
char *ft_getenv(char *var, char **env);
int ft_is_quote_active(char *input, int ind);

// signal.c

void ft_handle_sigint(int sig);
void ft_handle_sigquit(int sig);
void ft_signal_handler();

// lexer.c

char *ft_next_token_value(char *input, int *ind);
t_token_type ft_get_token_type(char *value);
int ft_add_token(t_token **tab, t_token_type type, char *value);
t_token **ft_lexer(t_shell *shell);

// nexttokenvalueutils.c

int ft_handle_pipe_token(char *input, int *ind, char **tokenvalueadress);
int ft_handle_redirin_token(char *input, int *ind, char **tokenvalueadress);
int ft_handle_redirout_token(char *input, int *ind, char **tokenvalueadress);
int ft_handle_no_word_token(char *input, int *ind, char **tokenvalueadress);
int ft_handle_word_token(char *input, int *ind, char **tokenvalueadress);

// isquoteactive.c

void ft_handle_simple_quote(int *sq, int *dq, int *last);
void ft_handle_double_quote(int *sq, int *dq, int *last);

#endif
