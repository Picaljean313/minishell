/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anony <anony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 18:13:42 by anony             #+#    #+#             */
/*   Updated: 2025/08/08 16:26:08 by anony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ctxt	*ft_get_hd_ctx(t_ctxt *set)
{
	static t_ctxt	*ctx;

	if (set != NULL)
		ctx = set;
	return (ctx);
}

void	ft_free_heredoc_context(t_ctxt *hdctx)
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
