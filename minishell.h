/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:00:19 by anony             #+#    #+#             */
/*   Updated: 2025/08/11 18:04:26 by anony            ###   ########.fr       */
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
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>

extern volatile sig_atomic_t	g_signal;

typedef enum e_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_HEREDOC,
	REDIR_APPEND
}	t_type;

typedef enum e_context
{
	MAIN,
	HEREDOC,
	CHILD
}	t_context;

typedef struct s_token
{
	t_type			type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_type			type;
	char			*file;
	int				heredocfd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_command
{
	char				**args;
	t_redir				*redir;
	int					fdin;
	int					fdout;
	pid_t				pid;
	struct s_command	*next;
}	t_command;

typedef struct s_shell
{
	char		*input;
	char		**env;
	char		**export;
	t_token		*tokens;
	t_command	*commands;
	int			exitcode;
}	t_shell;

typedef struct s_vlim
{
	int	start;
	int	end;
}	t_vlim;

typedef struct s_line
{
	char			*value;
	struct s_line	*next;
}	t_line;

typedef struct s_savedfds
{
	int	fdin;
	int	fdout;
	int	fderr;
}	t_savedfds;

typedef struct s_hdctxt
{
	char	*value;
	t_line	*lines;
	int		fd;
	t_shell	*shell;
}	t_ctxt;

typedef struct s_exec
{
	int			prevfd;
	int			nbcom;
	int			i;
	pid_t		pid;
	char		*path;
	t_command	*command;
}	t_exec;

typedef struct s_exut
{
	char	*path;
	char	**splitpath;
	char	*cmdpath;
	char	*cmd;
	int		i;
}	t_exut;

// signal.c

void	ft_signal_handler(t_context context);

// parsing.c

int		ft_parsing(t_shell *shell);

//  PARSING

// checkcommands.c

int		ft_check_empty_command(t_token *token);
int		ft_check_command(t_token *token);
int		ft_check_commands(t_shell *shell);

// checkinput.c

int		ft_check_wrong_operator(char *input, int ind);
int		ft_check_input(char *input);

// clean.c

void	ft_free_env_and_export(t_shell *shell);
void	ft_free_input(t_shell *shell);
void	ft_free_tokens(t_shell *shell);
void	ft_clean_line(t_shell *shell);
void	ft_clean_shell(t_shell *shell);

// cleanbis.c

void	ft_free_command_args(t_command *command);
void	ft_free_command_redir(t_command *command);
void	ft_free_commands(t_shell *shell);

// commandargs.c

void	ft_free_args(char **args, int ind);
int		ft_args_len(t_command *command);
int		ft_add_arg(t_token *token, t_command *command);

// commandredirs.c

int		ft_add_redir(t_token *token, t_command *command);

// envvar.c

char	*ft_get_var_value(char **valad, t_vlim *varlim, char **env);
void	ft_fill_val(char **valad, t_vlim *varlim, char **newvalue, char **env);
int		ft_handle_var(char **valad, t_vlim *varlim, char **env);

// exitvar.c

void	ft_fill_exit(char **valad, t_vlim *varlim, char **newvalue);
int		ft_handle_var_exit_status(char **valad, t_vlim *varlim);

// expand.c

int		ft_noemp(char *str);
void	ft_remove_first_empty_tokens(t_shell *shell);
void	ft_remove_empty_tokens(t_shell *shell);
int		ft_expand(t_shell *shell);

// heredoc

void	ft_free_lines(t_line *lines);
t_ctxt	*ft_get_hd_ctx(t_ctxt *set);
int		ft_heredoc(char *lim, t_shell *shell);
int		ft_handle_heredocs(t_shell *shell);

// initshell.c

int		ft_check_params(int argc, char **argv, char **env);
int		ft_set_shlvl(char **env);
char	**ft_set_env(char **env);
int		ft_init_shell(t_shell *shell, char **envp);

// isquoteactive.c

void	ft_handle_simple_quote(int *sq, int *dq, int *last);
void	ft_handle_double_quote(int *sq, int *dq, int *last);
int		ft_is_quote_active(char *input, int ind);
int		ft_is_simple_quote_active(char *value, int ind);

// lexer.c

char	*ft_next_token_value(char *input, int *ind);
t_type	ft_get_token_type(char *value);
int		ft_add_token(t_shell *shell, t_token *token);
int		ft_lexer(t_shell *shell);

// nexttokenvalue.c

int		ft_handle_pipe_token(char *input, int *ind, char **tokenvalueadress);
int		ft_handle_redirin_token(char *input, int *ind, char **tokenvalueadress);
int		ft_handle_redirout_token(char *input, int *ind, char **tokenvalueadr);
int		ft_handle_no_word_token(char *input, int *ind, char **tokenvalueadress);
int		ft_handle_word_token(char *input, int *ind, char **tokenvalueadress);

// parser.c

int		ft_init_command(t_command *command);
int		ft_fill_command_bis(t_token *token, t_command *command);
int		ft_fill_command(t_command *com, t_token *token, t_shell *shell);
int		ft_parser(t_shell *shell);

// removequotes.c

void	ft_handle_quote_bis(char **valad, int start, int end, char *newvalue);
int		ft_handle_quote(char **valad, int start, int end);
int		ft_remove_quotes(char **valad);

// replacevars.c

int		ft_handle_exit_and_var(char **valad, int *ind, char **env);
int		ft_replace_vars(char **valad, t_shell *shell);

// utils.c

void	ft_free_token(t_token *token);
char	*ft_truncate(char *str, int start, int end);
char	*ft_getenv(char *var, char **env);
void	ft_free_lines(t_line *lines);
int		ft_add_line(t_line **lines, char *value);

// utils2.c

t_ctxt	*ft_get_hd_ctx(t_ctxt *set);
void	ft_free_heredoc_context(t_ctxt *hdctx);

//  EXEC

// exec.c

int		ft_create_std_dup(t_savedfds *fds);
int		ft_restore_savedfd(t_savedfds *fds);
int		ft_exec_simple_builtin(t_command *com, t_shell *shell, t_savedfds *fds);
int		ft_exec(t_shell *shell);

// exec2.c

int		ft_has_output_redir(t_redir *redir);
int		ft_simple_builtin(t_shell *shell, t_savedfds *fds);
void	ft_init_exec(t_exec *exec, t_shell *shell);
void	ft_child_redir(t_shell *shell, t_exec *exec, t_savedfds *fds);

// exec3.c

int		ft_create_std_dup(t_savedfds *fds);
void	ft_close_savedfd(t_savedfds *fds);
int		ft_restore_savedfd(t_savedfds *fds);
int		ft_exec_simple_builtin(t_command *com, t_shell *shell, t_savedfds *fds);
void	ft_parent(t_exec *exec, int fd);

// utils.c

void	ft_close_fd(int *fd);
int		ft_is_builtin(t_command *command);
int		ft_exec_builtin(t_command *com, t_shell *sh, t_savedfds *fds, int sb);
int		ft_wait_pids(t_shell *shell);
int		ft_nb_commands(t_shell *shell);

// utils2.c

char	*ft_create_path(char *path, char *cmd);
void	ft_free_split_path(char **tab);
char	*ft_get_path(t_exec *exec, t_shell *shell);
void	ft_close_command_heredoc(t_command *command);
void	ft_close_heredoc(t_shell *shell);

// utils3.c

int		ft_last_redir_out(t_redir *redir);
int		ft_last_redir_in(t_redir *redir);
void	ft_print_after_signal(int status, int *newline, int *coredump);

// utils4.c

void	ft_clean_exec_child(t_shell *shell, t_exec *exec);

// redir.c

int		ft_redir_heredoc(t_redir *redir);
int		ft_redir_input(t_redir *redir);
int		ft_redirout(t_redir *redir);
int		ft_redir(t_redir *redir);

// BUILTIN

// cd.c

int		ft_set_env_value(char *value, char *var, t_shell *shell);
int		ft_cd(t_command *command, t_shell *shell);

// echo.c

int		ft_echo(t_command *command);

// env.c

int		ft_env(t_command *command, t_shell *shell);

// exit.c

int		ft_exit(t_command *command, t_shell *shell, t_savedfds *fds, int sb);

// export

char	*ft_get_var(char *str);
char	*ft_create_export_var(char *value);
int		ft_export(t_command *command, t_shell *shell);

// pwd.c

int		ft_pwd(t_command *command);

// unset.c

int		ft_unset(t_command *command, t_shell *shell);

// utils.c

int		ft_replace_env_var(char *arg, t_shell *shell);
int		ft_add_env_value(char *value, t_shell *shell);

// utils2.c

int		ft_set_export_no_value(char *var, t_shell *shell);
int		ft_set_export_value(char *arg, t_shell *shell);
int		ft_check_unset_var(char *var);

#endif
