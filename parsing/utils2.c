/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 18:13:42 by anony             #+#    #+#             */
/*   Updated: 2025/08/06 18:34:41 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_hdcontext	*ft_get_hd_ctx(t_hdcontext *set)
{
	static t_hdcontext	*ctx;

	if (set != NULL)
		ctx = set;
	return (ctx);
}

void	ft_free_heredoc_context(t_hdcontext *hdctx)
{
	if (!hdctx)
		return ;
	if (hdctx->value)
	{
		free(hdctx->value);
		hdctx->value = NULL;
	}
	ft_free_lines(hdctx->lines);
	ft_close_fd(&hdctx->fd);
	ft_clean_shell(hdctx->shell);
	free(hdctx);
}
