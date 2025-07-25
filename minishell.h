/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:00:19 by anony             #+#    #+#             */
/*   Updated: 2025/07/25 17:06:49 by anony            ###   ########.fr       */
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

typedef struct s_command
{
	char			*cmd;
	char			**args;
	t_redir			*redirin;
	t_redir			*redirout;
	struct s_command	*next;
}	t_command;

typedef struct s_shell
{
	char	*input;
	char	**env;
	t_token	*tokens;
	t_command	*commands;
	int		exitcode;
}	t_shell;

typedef struct s_varlimits
{
	int start;
	int end;
} t_varlimits;

// signal.c

void ft_handle_sigint(int sig);
void ft_signal_handler();

// parsing.c

int ft_parsing(t_shell *shell);

//  PARSING

// checkcommands.c

int ft_check_empty_command(t_token *token);
int ft_check_command(t_token *token);
int ft_check_commands(t_shell *shell);

// checkinput.c

int ft_check_wrong_operator(char *input, int ind);
int ft_check_input(char *input);

// clean.c

void ft_free_env(t_shell *shell);
void ft_free_input(t_shell *shell);
void ft_free_tokens(t_shell *shell);
void ft_clean_line(t_shell *shell);
void ft_clean_shell(t_shell *shell);

// cleanbis.c

void ft_free_command_args(t_command *command);
void ft_free_command_redirin(t_command *command);
void ft_free_command_redirout(t_command *command);
void ft_free_commands(t_shell *shell);

// commandargs.c

void ft_free_args(char **args, int ind);
int ft_args_len(t_command *command);
int ft_add_arg(t_token *token, t_command *command);

// commandredirs.c

void ft_add_redirin(t_redir *redir, t_token *token, t_command *command);
void ft_add_redirout(t_redir *redir, t_token *token, t_command *command);
int ft_add_redir(t_token *token, t_command *command);

// envvar.c

char *ft_get_var_value(char **valad, t_varlimits *varlim, char **env);
void ft_fill_new_value_var(char **valad, t_varlimits *varlim, char **newvalue, char **env);
int ft_handle_var(char **valad, t_varlimits *varlim, char **env);

// exitvar.c

void ft_fill_new_value_exit(char **valad, t_varlimits *varlim, char **newvalue);
int ft_handle_var_exit_status(char **valad, t_varlimits *varlim);

// expand.c

int ft_not_only_spaces(char *str);
void ft_remove_first_empty_tokens(t_shell *shell);
void ft_remove_empty_tokens(t_shell *shell);
int ft_expand(t_shell *shell);

// initshell.c

int ft_check_params(int argc, char **argv, char **env);
int	ft_set_shlvl(char **env);
char	**ft_set_env(char **env);
int	ft_init_shell(t_shell *shell, char **envp);

// isquoteactive.c

void ft_handle_simple_quote(int *sq, int *dq, int *last);
void ft_handle_double_quote(int *sq, int *dq, int *last);
int ft_is_quote_active(char *input, int ind);
int ft_is_simple_quote_active(char *value, int ind);

// lexer.c

char *ft_next_token_value(char *input, int *ind);
t_token_type ft_get_token_type(char *value);
int ft_add_token(t_shell *shell, t_token *token);
int ft_lexer(t_shell *shell);

// nexttokenvalue.c

int ft_handle_pipe_token(char *input, int *ind, char **tokenvalueadress);
int ft_handle_redirin_token(char *input, int *ind, char **tokenvalueadress);
int ft_handle_redirout_token(char *input, int *ind, char **tokenvalueadress);
int ft_handle_no_word_token(char *input, int *ind, char **tokenvalueadress);
int ft_handle_word_token(char *input, int *ind, char **tokenvalueadress);

// parser.c

int ft_init_command(t_command *command);
int ft_fill_command_bis(t_token *token, t_command *command);
int ft_fill_command(t_command *com, t_token *token, t_shell *shell);
int ft_parser(t_shell *shell);

// removequotes.c

void ft_handle_quote_bis(char **valad, int start, int end, char *newvalue);
int ft_handle_quote(char **valad, int start, int end);
int ft_remove_quotes(char **valad);

// replacevars.c

int ft_handle_exit_and_var(char **valad, int *ind, char **env);
int ft_replace_vars(char **valad, t_shell *shell);

// utils.c

void ft_free_token(t_token *token);
char *ft_truncate(char *str, int start, int end);
char *ft_getenv(char *var, char **env);




// // initshell.c

// int ft_check_params(int argc, char **argv, char **env);
// int	ft_init_shell(t_shell *shell, char **envp);

// // setenv.c

// int	ft_set_shlvl(char **env);
// char	**ft_set_env(char **env);

// // cleanshell.c

// void ft_free_env(char **env);
// void ft_free_token_tab(t_token *tokens);
// void ft_clean_shell(t_shell *shell);
// void ft_clean_line(t_shell *shell);

// // utils.c

// char *ft_truncate(char *str, int start, int end);
// char *ft_getenv(char *var, char **env);
// int ft_is_quote_active(char *input, int ind);

// // signal.c

// void ft_handle_sigint(int sig);
// void ft_signal_handler();

// // lexer.c

// char *ft_next_token_value(char *input, int *ind);
// t_token_type ft_get_token_type(char *value);
// int ft_add_token(t_token **tab, t_token_type type, char *value);
// t_token *ft_lexer(t_shell *shell);

// // nexttokenvalueutils.c

// int ft_handle_pipe_token(char *input, int *ind, char **tokenvalueadress);
// int ft_handle_redirin_token(char *input, int *ind, char **tokenvalueadress);
// int ft_handle_redirout_token(char *input, int *ind, char **tokenvalueadress);
// int ft_handle_no_word_token(char *input, int *ind, char **tokenvalueadress);
// int ft_handle_word_token(char *input, int *ind, char **tokenvalueadress);

// // isquoteactive.c

// void ft_handle_simple_quote(int *sq, int *dq, int *last);
// void ft_handle_double_quote(int *sq, int *dq, int *last);
// int ft_is_quote_active(char *input, int ind);
// int ft_is_simple_quote_active(char *input, int ind);

// // replacevars.c

// int ft_handle_exit_and_var(char **valad, int *ind, char **env);
// int ft_replace_vars(char **valad, t_shell *shell);

// // exitvar.c

// void ft_fill_new_value_exit(char **valad, t_varlimits *varlim, char **newvalue);
// int ft_handle_var_exit_status(char **valad, t_varlimits *varlim);

// // envvar.c

// char *ft_get_var_value(char **valad, t_varlimits *varlim, char **env);
// void ft_fill_new_value_var(char **valad, t_varlimits *varlim, char **newvalue, char **env);
// int ft_handle_var(char **valad, t_varlimits *varlim, char **env);

// // checkpipes.c

// int ft_check_empty_pipe(t_token **tab);
// int ft_check_pipe(t_token *token);
// int ft_check_pipes(t_token **tab);

// // expand.c

// int ft_expand(t_shell *shell);

// // removequotes.c

// void ft_handle_quote_bis(char **valad, int start, int end, char *newvalue);
// int ft_handle_quote(char **valueadress, int start, int end);
// int ft_remove_quotes(char **valad);

// // parser.c

// t_pipe **ft_parser(t_token **tokentab);

// // fillpipe.c

// int ft_init_pipe(t_pipe *pipe);
// int ft_fill_pipe_bis(t_token *token, t_pipe *pipe);
// int ft_fill_pipe(t_token *token, t_pipe **pipetab);

// // argsredirs.c

// void ft_add_redirin(t_redir *redir, t_token *token, t_pipe *pipe);
// void ft_add_redirout(t_redir *redir, t_token *token, t_pipe *pipe);
// int ft_add_redir(t_token *token, t_pipe *pipe);
// int ft_add_arg(t_token *token, t_pipe *pipe);

// // checkinput.c

// int ft_check_wrong_operator(char *input, int ind);
// int ft_check_input(char *input);

// // parsing.c

// int ft_parsing(t_shell *shell);

#endif
