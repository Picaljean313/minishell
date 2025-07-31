/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:06:28 by anony             #+#    #+#             */
/*   Updated: 2025/07/31 16:34:04 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_pwd(t_command *command)
{
    char *cwd;

    if (!command->args || ft_strncmp(command->args[0], "pwd", 4) != 0)
		return (1);
    cwd = getcwd(NULL, 0);
    if (!cwd)
        return (perror("getcwd"), 1);
    printf("%s\n", cwd);
    free(cwd);
    return (0);
}