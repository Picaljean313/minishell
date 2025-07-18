/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:00:19 by anony             #+#    #+#             */
/*   Updated: 2025/07/18 12:55:58 by anony            ###   ########.fr       */
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

void	ft_init_shell(t_shell *shell, char **envp);
int	ft_set_shlvl(char **env);
void	ft_free_env_ind(char **env, int ind);
char	**ft_set_env(char **env);

// cleanshell.c

void ft_free_env(char ***env);
void ft_clean_shell(t_shell *shell);

// utils.c

char *ft_getenv(char *var, char **env);

#endif
