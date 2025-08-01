/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 17:52:54 by anony             #+#    #+#             */
/*   Updated: 2025/08/01 21:33:54 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_free_lines(t_line *lines)
{
    t_line *temp;

	if (!lines)
		return ;
	while (lines)
	{
		temp = lines;
		lines = lines->next;
		if (temp->value)
		{
			free(temp->value);
			temp->value = NULL;
		}
		free(temp);
		temp = NULL;
	}
	return ;
}

void ft_add_line(t_line **lines, char *value)
{
    t_line *line;
    t_line *temp;

    line = malloc(sizeof(t_line));
    line->value = ft_strdup(value);
    line->next = NULL;
    if (!*lines)
        *lines = line;
    else
    {
        temp = *lines;
        while (temp->next)
            temp = temp->next;
        temp->next = line;
    }
}

int ft_fill_heredoc(char *lim, int fd)
{
    t_line *lines;
    t_line *temp;
    char    *value;

    lines = NULL;
    while (1)
    {
        value = readline("> ");
        if (!value)
            break ;
        if (ft_strncmp(value, lim, ft_strlen(lim) + 1) == 0)
        {
            free(value);
            break ;
        }
        ft_add_line(&lines, value);
    }
    temp = lines;
    while (temp)
    {
        write(fd, temp->value, ft_strlen(temp->value));
        write(fd, "\n", 1);
        temp = temp->next;
    }
    ft_free_lines(lines);
    ft_close_fd(&fd);
    exit(0);
}

int ft_heredoc(char *lim)
{
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1)
        return (perror("pipe"), 1);
    pid = fork();
    if (pid < 0)
        return (perror("fork"), 1);
    else if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        ft_close_fd(&pipefd[0]);
        ft_fill_heredoc(lim, pipefd[1]);
        exit(0);
    }
    else
    {
        signal(SIGINT, SIG_IGN);
        ft_close_fd(&pipefd[1]);
        if (waitpid(pid, NULL, 0) == -1)
            return (perror("waitpid"), 1);
        return (pipefd[0]);
    }
}
