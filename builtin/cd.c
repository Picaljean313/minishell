/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:05:58 by anony             #+#    #+#             */
/*   Updated: 2025/08/10 18:47:04 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_new_path(t_command *command, char *cwd, t_shell *shell)
{
	char	*newpath;
	char	*temp;

	if (!command->args[1])
	{
		newpath = ft_getenv("HOME", shell->env);
		if (!newpath)
			newpath = ft_strdup("/");
		return (newpath);
	}
	if (command->args[1][0] == '/')
		return (ft_strdup(command->args[1]));
	temp = ft_strjoin("/", command->args[1]);
	if (!temp)
		return (NULL);
	newpath = ft_strjoin(cwd, temp);
	free(temp);
	if (!newpath)
		return (NULL);
	return (newpath);
}

int	ft_set_env_value(char *value, char *var, t_shell *shell)
{
	int		i;
	char	*newvalue;

	if (!value)
		return (1);
	newvalue = ft_strjoin(var, value);
	if (!newvalue)
		return (1);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], var, (int)ft_strlen(var)) == 0)
		{
			free(shell->env[i]);
			shell->env[i] = newvalue;
			return (0);
		}
		i++;
	}
	if (ft_add_env_value(newvalue, shell) != 0)
		return (1);
	return (0);
}

int	ft_cd(t_command *command, t_shell *shell)
{
	char	*cwd;
	char	*newpath;
	char	*oldcwd;

	(void)shell;
	if (!command->args || ft_strncmp(command->args[0], "cd", 3) != 0)
		return (1);
	oldcwd = getcwd(NULL, 0);
	if (!oldcwd)
		return (perror("getcwd"), 1);
	newpath = ft_new_path(command, oldcwd, shell);
	if (!newpath)
		return (free(oldcwd), 1);
	if (chdir(newpath) == -1)
		return (free(oldcwd), free(newpath), perror("chdir"), 1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (free(oldcwd), free(newpath), perror("getcwd"), 1);
	if (ft_set_env_value(oldcwd, "OLDPWD=", shell) != 0)
		return (free(cwd), free(newpath), free(oldcwd), 1);
	if (ft_set_env_value(cwd, "PWD=", shell) != 0)
		return (free(cwd), free(newpath), free(oldcwd), 1);
	return (free(cwd), free(newpath), free(oldcwd), g_signal = 0, 0);
}

// pour voir le path :
// void	ft_show_bis(char **tab)
// {
// 	int	i;
// 	i = 0;
// 	if (!tab)
// 	{
// 		printf("no tab\n");
// 		return ;
// 	}
// 	printf("start\n");
// 	while (tab[i])
// 	{
// 		printf("%s\n", tab[i]);
// 		i++;
// 	}
// 	printf("end\n");
// }
// A la fin de cd avant le return:
//    char *avirer;
//     avirer = ft_getenv("PWD", shell->env);
//     printf("%s\n", avirer);
//     free(avirer);
