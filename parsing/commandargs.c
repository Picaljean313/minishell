/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandargs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:41:27 by anony             #+#    #+#             */
/*   Updated: 2025/07/25 16:43:44 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_free_args(char **args, int ind)
{
    int i;
    
    i = 0;
    if (!args)
        return ;
    while (i < ind)
    {
        free(args[i]);
        i++;
    }
    free(args);
}

int ft_args_len(t_command *command)
{
    int len;

    len = 0;
    if (command->args)
    {
        while (command->args[len])
            len++;
    }
    return (len);
}

int ft_add_arg(t_token *token, t_command *command)
{
    int i;
    int len;
    char **args;

    len = ft_args_len(command);
    args = malloc((len + 2) * sizeof(char *));
    if (args == NULL)
        return (1);
    i = 0;
    while (i < len)
    {
        args[i] = ft_strdup(command->args[i]);
        if (!args[i])
            return (ft_free_args(args, i), 1);
        free(command->args[i]);
        i++;
    }
    args[i] = ft_strdup(token->value);
    if (!args[i])
        return (ft_free_args(args, i), 1);
    args[i + 1] = NULL;
    free(command->args);
    command->args = args;
    return (0);
}
