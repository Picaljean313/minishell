/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:01:21 by anony             #+#    #+#             */
/*   Updated: 2025/08/11 20:19:24 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_clean_exec_child(t_shell *shell, t_exec *exec)
{
	ft_close_heredoc(shell);
	ft_clean_shell(shell);
	free(exec);
}
